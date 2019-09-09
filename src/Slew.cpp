
#include "Slew.hpp"

bool Slew::active() {
	return inputs[IN_INPUT].isConnected() && outputs[OUT_OUTPUT].isConnected();
}

void Slew::modulate() {
	float riseTime = time(params[RISE_PARAM], inputs[RISE_INPUT]);
	float riseShape = shape(params[RISE_SHAPE_PARAM]);
	float fallTime = time(params[FALL_PARAM], inputs[FALL_INPUT]);
	float fallShape = shape(params[FALL_SHAPE_PARAM]);

	_rise.setParams(APP->engine->getSampleRate(), riseTime, riseShape);
	_fall.setParams(APP->engine->getSampleRate(), fallTime, fallShape);
}

void Slew::processChannel(const ProcessArgs& args, int _c) {
	float sample = inputs[IN_INPUT].getVoltageSum();
	if (sample > _last) {
		if (!_rising) {
			_rising = true;
			_rise._last = _last;
		}
		outputs[OUT_OUTPUT].setVoltage(_last = _rise.next(sample));
	}
	else {
		if (_rising) {
			_rising = false;
			_fall._last = _last;
		}
		outputs[OUT_OUTPUT].setVoltage(_last = _fall.next(sample));
	}
}

float Slew::time(Param& param, Input& input) {
	float time = param.getValue();
	if (input.isConnected()) {
		time *= clamp(input.getVoltage() / 10.0f, 0.0f, 1.0f);
	}
	return time * time * 10000.0f;
}

float Slew::shape(Param& param) {
	float shape = param.getValue();
	if (shape < 0.0) {
		shape = 1.0f + shape;
		shape = _rise.minShape + shape * (1.0f - _rise.minShape);
	}
	else {
		shape += 1.0f;
	}
	return shape;
}

struct SlewWidget : ModuleWidget {
	static constexpr int hp = 3;

	SlewWidget(Slew* module) {
		setModule(module);
		box.size = Vec(RACK_GRID_WIDTH * hp, RACK_GRID_HEIGHT);

		{
			SvgPanel *panel = new SvgPanel();
			panel->box.size = box.size;
			panel->setBackground(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Slew.svg")));
			addChild(panel);
		}

		addChild(createWidget<ScrewSilver>(Vec(0, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 15, 365)));

		// generated by svg_widgets.rb
		auto riseParamPosition = Vec(9.5, 34.0);
		auto riseShapeParamPosition = Vec(14.5, 76.0);
		auto fallParamPosition = Vec(9.5, 155.0);
		auto fallShapeParamPosition = Vec(14.5, 197.0);

		auto riseInputPosition = Vec(10.5, 105.0);
		auto fallInputPosition = Vec(10.5, 226.0);
		auto inInputPosition = Vec(10.5, 263.0);

		auto outOutputPosition = Vec(10.5, 301.0);
		// end generated by svg_widgets.rb

		addParam(createParam<Knob26>(riseParamPosition, module, Slew::RISE_PARAM));
		addParam(createParam<Knob16>(riseShapeParamPosition, module, Slew::RISE_SHAPE_PARAM));
		addParam(createParam<Knob26>(fallParamPosition, module, Slew::FALL_PARAM));
		addParam(createParam<Knob16>(fallShapeParamPosition, module, Slew::FALL_SHAPE_PARAM));

		addInput(createInput<Port24>(riseInputPosition, module, Slew::RISE_INPUT));
		addInput(createInput<Port24>(fallInputPosition, module, Slew::FALL_INPUT));
		addInput(createInput<Port24>(inInputPosition, module, Slew::IN_INPUT));

		addOutput(createOutput<Port24>(outOutputPosition, module, Slew::OUT_OUTPUT));
	}
};

Model* modelSlew = bogaudio::createModel<Slew, SlewWidget>("Bogaudio-Slew", "Slew", "slew / lag / glide", "Slew limiter");
