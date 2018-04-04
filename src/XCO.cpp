
#include "XCO.hpp"
#include "dsp/pitch.hpp"

void XCO::onReset() {
	_syncTrigger.reset();
	_modulationStep = modulationSteps;
	_triangleSampleStep = _phasor._sampleRate;
}

void XCO::onSampleRateChange() {
	_phasor.setSampleRate(engineGetSampleRate());
	_modulationStep = modulationSteps;
	_triangleSampleStep = _phasor._sampleRate;
}

void XCO::step() {
	lights[SLOW_LIGHT].value = _slowMode = ((int)params[SLOW_PARAM].value) == 1;
	_fmLinearMode = ((int)params[FM_TYPE_PARAM].value) == 1;
	lights[FM_EXP_LIGHT].value = !_fmLinearMode;
	lights[FM_LIN_LIGHT].value = _fmLinearMode;

	if (!(
		outputs[MIX_OUTPUT].active ||
		outputs[SQUARE_OUTPUT].active ||
		outputs[SAW_OUTPUT].active ||
		outputs[TRIANGLE_OUTPUT].active ||
		outputs[SINE_OUTPUT].active
	)) {
		return;
	}

	++_modulationStep;
	if (_modulationStep >= modulationSteps) {
		_modulationStep = 0;

		_baseVOct = params[FREQUENCY_PARAM].value;
		_baseVOct += params[FINE_PARAM].value;
		if (inputs[PITCH_INPUT].active) {
			_baseVOct += clamp(inputs[PITCH_INPUT].value, -5.0f, 5.0f);
		}
		if (_slowMode) {
			_baseVOct -= 5.0f;
		}
		_baseHz = cvToFrequency(_baseVOct);

		if (_syncTrigger.process(inputs[SYNC_INPUT].value)) {
			_phasor.setPhase(0.0f);
		}

		float pw = params[SQUARE_PW_PARAM].value;
		if (inputs[SQUARE_PW_INPUT].active) {
			pw *= clamp(inputs[SQUARE_PW_INPUT].value / 5.0f, -1.0f, 1.0f);
		}
		pw = (pw + 1.0f) / 2.0f;
		pw *= 1.0f - 2.0f * _square.minPulseWidth;
		_square.setPulseWidth(pw);

		float saturation = params[SAW_SATURATION_PARAM].value;
		if (inputs[SAW_SATURATION_INPUT].active) {
			saturation *= clamp(inputs[SAW_SATURATION_INPUT].value / 10.0f, 0.0f, 1.0f);
		}
		_saw.setSaturation(saturation * 10.f);

		_sineFeedback = params[SINE_FEEDBACK_PARAM].value;
		if (inputs[SINE_FEEDBACK_INPUT].active) {
			_sineFeedback *= clamp(inputs[SINE_FEEDBACK_INPUT].value / 10.0f, 0.0f, 1.0f);
		}

		float sample = params[TRIANGLE_SAMPLE_PARAM].value;
		if (inputs[TRIANGLE_SAMPLE_INPUT].active) {
			sample *= clamp(inputs[TRIANGLE_SAMPLE_INPUT].value / 10.0f, 0.0f, 1.0f);
		}
		float maxSampleSteps = (_phasor._sampleRate / _phasor._frequency) / 4.0f;
		_triangleSampleSteps = clamp((int)(sample * maxSampleSteps), 1, (int)maxSampleSteps);

		_fmDepth = params[FM_PARAM].value;

		_squarePhaseOffset = phaseOffset(params[SQUARE_PHASE_PARAM], inputs[SQUARE_PHASE_INPUT]);
		_sawPhaseOffset = phaseOffset(params[SAW_PHASE_PARAM], inputs[SAW_PHASE_INPUT]);
		_trianglePhaseOffset = phaseOffset(params[TRIANGLE_PHASE_PARAM], inputs[TRIANGLE_PHASE_INPUT]);
		_sinePhaseOffset = phaseOffset(params[SINE_PHASE_PARAM], inputs[SINE_PHASE_INPUT]);

		_squareMix = level(params[SQUARE_MIX_PARAM], inputs[SQUARE_MIX_INPUT]);
		_sawMix = level(params[SAW_MIX_PARAM], inputs[SAW_MIX_INPUT]);
		_triangleMix = level(params[TRIANGLE_MIX_PARAM], inputs[TRIANGLE_MIX_INPUT]);
		_sineMix = level(params[SINE_MIX_PARAM], inputs[SINE_MIX_INPUT]);
	}

	bool fmOn = false;
	float phaseOffset = 0.0f;
	if (inputs[FM_INPUT].active && _fmDepth > 0.01f) {
		fmOn = true;
		float fm = inputs[FM_INPUT].value * _fmDepth;
		if (_fmLinearMode) {
			_phasor.setFrequency(_baseHz);
			phaseOffset = Phasor::radiansToPhase(2.0f * fm);
		}
		else {
			_phasor.setFrequency(cvToFrequency(_baseVOct + fm));
		}
	}
	else {
		_phasor.setFrequency(_baseHz);
	}
	float sineFeedbackOffset = 0.0f;
	if (_sineFeedback > 0.001f) {
		sineFeedbackOffset = Phasor::radiansToPhase(_sineFeedback * _phasor.next());
	}
	else {
		_phasor.advancePhase();
	}
	float mix = 0.0f;
	if (outputs[MIX_OUTPUT].active || outputs[SQUARE_OUTPUT].active) {
		mix += outputs[SQUARE_OUTPUT].value = amplitude * _squareMix * _square.nextFromPhasor(_phasor, _squarePhaseOffset + phaseOffset);
	}
	if (outputs[MIX_OUTPUT].active || outputs[SAW_OUTPUT].active) {
		mix += outputs[SAW_OUTPUT].value = amplitude * _sawMix * _saw.nextFromPhasor(_phasor, _sawPhaseOffset + phaseOffset);
	}
	if (outputs[MIX_OUTPUT].active || outputs[TRIANGLE_OUTPUT].active) {
		bool useSample = false;
		if (_triangleSampleSteps > 1) {
			++_triangleSampleStep;
			if (_triangleSampleStep < _triangleSampleSteps) {
				useSample = true;
			}
			else {
				_triangleSampleStep = 0;
			}
		}

		if (fmOn && _fmLinearMode) {
			if (!useSample) {
				_triangleSample = _phasor._phase;
			}
			mix += outputs[TRIANGLE_OUTPUT].value = amplitude * _triangleMix * _triangle.nextForPhase(_triangleSample + _trianglePhaseOffset + phaseOffset);
		}
		else {
			if (useSample) {
				mix += outputs[TRIANGLE_OUTPUT].value = _triangleSample;
			}
			else {
				mix += outputs[TRIANGLE_OUTPUT].value = _triangleSample = amplitude * _triangleMix * _triangle.nextFromPhasor(_phasor, _trianglePhaseOffset + phaseOffset);
			}
		}
	}
	if (outputs[MIX_OUTPUT].active || outputs[SINE_OUTPUT].active) {
		mix += outputs[SINE_OUTPUT].value = amplitude * _sineMix * _sine.nextFromPhasor(_phasor, sineFeedbackOffset + _sinePhaseOffset + phaseOffset);
	}
	if (outputs[MIX_OUTPUT].active) {
		outputs[MIX_OUTPUT].value = mix;
	}
}

float XCO::phaseOffset(Param& param, Input& input) {
	float v = param.value;
	if (input.active) {
		v *= clamp(input.value / 5.0f, -1.0f, 1.0f);
	}
	return -v;
}

float XCO::level(Param& param, Input& input) {
	float v = param.value;
	if (input.active) {
		v *= clamp(input.value / 10.0f, 0.0f, 1.0f);
	}
	return v;
}

struct XCOWidget : ModuleWidget {
	XCOWidget(XCO* module) : ModuleWidget(module) {
		box.size = Vec(RACK_GRID_WIDTH * 20, RACK_GRID_HEIGHT);

		{
			SVGPanel *panel = new SVGPanel();
			panel->box.size = box.size;
			panel->setBackground(SVG::load(assetPlugin(plugin, "res/XCO.svg")));
			addChild(panel);
		}

		addChild(Widget::create<ScrewSilver>(Vec(15, 0)));
		addChild(Widget::create<ScrewSilver>(Vec(box.size.x - 30, 0)));
		addChild(Widget::create<ScrewSilver>(Vec(15, 365)));
		addChild(Widget::create<ScrewSilver>(Vec(box.size.x - 30, 365)));

		// generated by svg_widgets.rb
		auto frequencyParamPosition = Vec(40.0, 45.0);
		auto fineParamPosition = Vec(65.5, 156.0);
		auto slowParamPosition = Vec(90.0, 191.7);
		auto fmParamPosition = Vec(61.0, 219.0);
		auto fmTypeParamPosition = Vec(82.0, 288.0);
		auto squarePwParamPosition = Vec(147.0, 60.0);
		auto squarePhaseParamPosition = Vec(147.0, 148.0);
		auto squareMixParamPosition = Vec(147.0, 237.0);
		auto sawSaturationParamPosition = Vec(187.0, 60.0);
		auto sawPhaseParamPosition = Vec(187.0, 148.0);
		auto sawMixParamPosition = Vec(187.0, 237.0);
		auto triangleSampleParamPosition = Vec(227.0, 60.0);
		auto trianglePhaseParamPosition = Vec(227.0, 148.0);
		auto triangleMixParamPosition = Vec(227.0, 237.0);
		auto sineFeedbackParamPosition = Vec(267.0, 60.0);
		auto sinePhaseParamPosition = Vec(267.0, 148.0);
		auto sineMixParamPosition = Vec(267.0, 237.0);

		auto fmInputPosition = Vec(34.0, 261.0);
		auto squarePwInputPosition = Vec(143.0, 95.0);
		auto squarePhaseInputPosition = Vec(143.0, 183.0);
		auto squareMixInputPosition = Vec(143.0, 272.0);
		auto sawSaturationInputPosition = Vec(183.0, 95.0);
		auto sawPhaseInputPosition = Vec(183.0, 183.0);
		auto sawMixInputPosition = Vec(183.0, 272.0);
		auto triangleSampleInputPosition = Vec(223.0, 95.0);
		auto trianglePhaseInputPosition = Vec(223.0, 183.0);
		auto triangleMixInputPosition = Vec(223.0, 272.0);
		auto sineFeedbackInputPosition = Vec(263.0, 95.0);
		auto sinePhaseInputPosition = Vec(263.0, 183.0);
		auto sineMixInputPosition = Vec(263.0, 272.0);
		auto pitchInputPosition = Vec(14.0, 318.0);
		auto syncInputPosition = Vec(52.0, 318.0);

		auto squareOutputPosition = Vec(143.0, 318.0);
		auto sawOutputPosition = Vec(183.0, 318.0);
		auto triangleOutputPosition = Vec(223.0, 318.0);
		auto sineOutputPosition = Vec(263.0, 318.0);
		auto mixOutputPosition = Vec(103.0, 318.0);

		auto slowLightPosition = Vec(50.0, 193.0);
		auto fmExpLightPosition = Vec(73.0, 264.0);
		auto fmLinLightPosition = Vec(73.0, 277.3);
		// end generated by svg_widgets.rb

		addParam(ParamWidget::create<Knob68>(frequencyParamPosition, module, XCO::FREQUENCY_PARAM, -3.0, 6.0, 0.0));
		addParam(ParamWidget::create<Knob16>(fineParamPosition, module, XCO::FINE_PARAM, -1.0, 1.0, 0.0));
		addParam(ParamWidget::create<StatefulButton9>(slowParamPosition, module, XCO::SLOW_PARAM, 0.0, 1.0, 0.0));
		addParam(ParamWidget::create<Knob26>(fmParamPosition, module, XCO::FM_PARAM, 0.0, 1.0, 0.0));
		addParam(ParamWidget::create<StatefulButton9>(fmTypeParamPosition, module, XCO::FM_TYPE_PARAM, 0.0, 1.0, 0.0));
		addParam(ParamWidget::create<Knob16>(squarePwParamPosition, module, XCO::SQUARE_PW_PARAM, -0.97, 0.97, 0.0));
		addParam(ParamWidget::create<Knob16>(squarePhaseParamPosition, module, XCO::SQUARE_PHASE_PARAM, -1.0, 1.0, 0.0));
		addParam(ParamWidget::create<Knob16>(squareMixParamPosition, module, XCO::SQUARE_MIX_PARAM, 0.0, 1.0, 1.0));
		addParam(ParamWidget::create<Knob16>(sawSaturationParamPosition, module, XCO::SAW_SATURATION_PARAM, 0.0, 1.0, 0.0));
		addParam(ParamWidget::create<Knob16>(sawPhaseParamPosition, module, XCO::SAW_PHASE_PARAM, -1.0, 1.0, 0.0));
		addParam(ParamWidget::create<Knob16>(sawMixParamPosition, module, XCO::SAW_MIX_PARAM, 0.0, 1.0, 1.0));
		addParam(ParamWidget::create<Knob16>(triangleSampleParamPosition, module, XCO::TRIANGLE_SAMPLE_PARAM, 0.0, 1.0, 0.0));
		addParam(ParamWidget::create<Knob16>(trianglePhaseParamPosition, module, XCO::TRIANGLE_PHASE_PARAM, -1.0, 1.0, 0.0));
		addParam(ParamWidget::create<Knob16>(triangleMixParamPosition, module, XCO::TRIANGLE_MIX_PARAM, 0.0, 1.0, 1.0));
		addParam(ParamWidget::create<Knob16>(sineFeedbackParamPosition, module, XCO::SINE_FEEDBACK_PARAM, 0.0, 1.0, 0.0));
		addParam(ParamWidget::create<Knob16>(sinePhaseParamPosition, module, XCO::SINE_PHASE_PARAM, -1.0, 1.0, 0.0));
		addParam(ParamWidget::create<Knob16>(sineMixParamPosition, module, XCO::SINE_MIX_PARAM, 0.0, 1.0, 1.0));

		addInput(Port::create<Port24>(fmInputPosition, Port::INPUT, module, XCO::FM_INPUT));
		addInput(Port::create<Port24>(squarePwInputPosition, Port::INPUT, module, XCO::SQUARE_PW_INPUT));
		addInput(Port::create<Port24>(squarePhaseInputPosition, Port::INPUT, module, XCO::SQUARE_PHASE_INPUT));
		addInput(Port::create<Port24>(squareMixInputPosition, Port::INPUT, module, XCO::SQUARE_MIX_INPUT));
		addInput(Port::create<Port24>(sawSaturationInputPosition, Port::INPUT, module, XCO::SAW_SATURATION_INPUT));
		addInput(Port::create<Port24>(sawPhaseInputPosition, Port::INPUT, module, XCO::SAW_PHASE_INPUT));
		addInput(Port::create<Port24>(sawMixInputPosition, Port::INPUT, module, XCO::SAW_MIX_INPUT));
		addInput(Port::create<Port24>(triangleSampleInputPosition, Port::INPUT, module, XCO::TRIANGLE_SAMPLE_INPUT));
		addInput(Port::create<Port24>(trianglePhaseInputPosition, Port::INPUT, module, XCO::TRIANGLE_PHASE_INPUT));
		addInput(Port::create<Port24>(triangleMixInputPosition, Port::INPUT, module, XCO::TRIANGLE_MIX_INPUT));
		addInput(Port::create<Port24>(sineFeedbackInputPosition, Port::INPUT, module, XCO::SINE_FEEDBACK_INPUT));
		addInput(Port::create<Port24>(sinePhaseInputPosition, Port::INPUT, module, XCO::SINE_PHASE_INPUT));
		addInput(Port::create<Port24>(sineMixInputPosition, Port::INPUT, module, XCO::SINE_MIX_INPUT));
		addInput(Port::create<Port24>(pitchInputPosition, Port::INPUT, module, XCO::PITCH_INPUT));
		addInput(Port::create<Port24>(syncInputPosition, Port::INPUT, module, XCO::SYNC_INPUT));

		addOutput(Port::create<Port24>(squareOutputPosition, Port::OUTPUT, module, XCO::SQUARE_OUTPUT));
		addOutput(Port::create<Port24>(sawOutputPosition, Port::OUTPUT, module, XCO::SAW_OUTPUT));
		addOutput(Port::create<Port24>(triangleOutputPosition, Port::OUTPUT, module, XCO::TRIANGLE_OUTPUT));
		addOutput(Port::create<Port24>(sineOutputPosition, Port::OUTPUT, module, XCO::SINE_OUTPUT));
		addOutput(Port::create<Port24>(mixOutputPosition, Port::OUTPUT, module, XCO::MIX_OUTPUT));

		addChild(ModuleLightWidget::create<SmallLight<GreenLight>>(slowLightPosition, module, XCO::SLOW_LIGHT));
		addChild(ModuleLightWidget::create<SmallLight<GreenLight>>(fmExpLightPosition, module, XCO::FM_EXP_LIGHT));
		addChild(ModuleLightWidget::create<SmallLight<GreenLight>>(fmLinLightPosition, module, XCO::FM_LIN_LIGHT));
	}
};

Model* modelXCO = Model::create<XCO, XCOWidget>("Bogaudio", "Bogaudio-XCO", "XCO", OSCILLATOR_TAG);
