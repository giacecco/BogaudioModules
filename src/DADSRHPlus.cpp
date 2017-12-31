
#include "DADSRHCore.hpp"

struct DADSRHPlus : Module {
	enum ParamsIds {
		DELAY_PARAM,
		ATTACK_PARAM,
		DECAY_PARAM,
		SUSTAIN_PARAM,
		RELEASE_PARAM,
		HOLD_PARAM,
		ATTACK_SHAPE_PARAM,
		DECAY_SHAPE_PARAM,
		RELEASE_SHAPE_PARAM,
		TRIGGER_PARAM,
		MODE_PARAM,
		LOOP_PARAM,
		SPEED_PARAM,
		RETRIGGER_PARAM,
		NUM_PARAMS
	};

	enum InputsIds {
		DELAY_INPUT,
		ATTACK_INPUT,
		DECAY_INPUT,
		SUSTAIN_INPUT,
		RELEASE_INPUT,
		HOLD_INPUT,
		TRIGGER_INPUT,
		NUM_INPUTS
	};

	enum OutputsIds {
		DELAY_OUTPUT,
		ATTACK_OUTPUT,
		DECAY_OUTPUT,
		SUSTAIN_OUTPUT,
		RELEASE_OUTPUT,
		ENV_OUTPUT,
		INV_OUTPUT,
		TRIGGER_OUTPUT,
		NUM_OUTPUTS
	};

	enum LightsIds {
		DELAY_LIGHT,
		ATTACK_LIGHT,
		DECAY_LIGHT,
		SUSTAIN_LIGHT,
		RELEASE_LIGHT,
		ATTACK_SHAPE1_LIGHT,
		ATTACK_SHAPE2_LIGHT,
		ATTACK_SHAPE3_LIGHT,
		DECAY_SHAPE1_LIGHT,
		DECAY_SHAPE2_LIGHT,
		DECAY_SHAPE3_LIGHT,
		RELEASE_SHAPE1_LIGHT,
		RELEASE_SHAPE2_LIGHT,
		RELEASE_SHAPE3_LIGHT,
		NUM_LIGHTS
	};

	DADSRHCore _core;

	DADSRHPlus() : Module(
		NUM_PARAMS,
		NUM_INPUTS,
		NUM_OUTPUTS,
		NUM_LIGHTS
	)
	, _core(
		params[DELAY_PARAM],
		params[ATTACK_PARAM],
		params[DECAY_PARAM],
		params[SUSTAIN_PARAM],
		params[RELEASE_PARAM],
		params[HOLD_PARAM],
		params[ATTACK_SHAPE_PARAM],
		params[DECAY_SHAPE_PARAM],
		params[RELEASE_SHAPE_PARAM],
		params[TRIGGER_PARAM],
		params[MODE_PARAM],
		params[LOOP_PARAM],
		params[SPEED_PARAM],
		params[RETRIGGER_PARAM],

		&inputs[DELAY_INPUT],
		&inputs[ATTACK_INPUT],
		&inputs[DECAY_INPUT],
		&inputs[SUSTAIN_INPUT],
		&inputs[RELEASE_INPUT],
		&inputs[HOLD_INPUT],
		inputs[TRIGGER_INPUT],

		&outputs[DELAY_OUTPUT],
		&outputs[ATTACK_OUTPUT],
		&outputs[DECAY_OUTPUT],
		&outputs[SUSTAIN_OUTPUT],
		&outputs[RELEASE_OUTPUT],
		outputs[ENV_OUTPUT],
		outputs[INV_OUTPUT],
		outputs[TRIGGER_OUTPUT],

		lights[DELAY_LIGHT],
		lights[ATTACK_LIGHT],
		lights[DECAY_LIGHT],
		lights[SUSTAIN_LIGHT],
		lights[RELEASE_LIGHT],
		lights[ATTACK_SHAPE1_LIGHT],
		lights[ATTACK_SHAPE2_LIGHT],
		lights[ATTACK_SHAPE3_LIGHT],
		lights[DECAY_SHAPE1_LIGHT],
		lights[DECAY_SHAPE2_LIGHT],
		lights[DECAY_SHAPE3_LIGHT],
		lights[RELEASE_SHAPE1_LIGHT],
		lights[RELEASE_SHAPE2_LIGHT],
		lights[RELEASE_SHAPE3_LIGHT]
	) {
		reset();
	}

	virtual void reset() override {
		_core.reset();
	}

	virtual void step() override {
		_core.step();
	}
};

DADSRHPlusWidget::DADSRHPlusWidget() {
	DADSRHPlus *module = new DADSRHPlus();
	setModule(module);
	box.size = Vec(RACK_GRID_WIDTH * 15, RACK_GRID_HEIGHT);

	{
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		panel->setBackground(SVG::load(assetPlugin(plugin, "res/DADSRHPlus.svg")));
		addChild(panel);
	}

	addChild(createScrew<ScrewSilver>(Vec(15, 0)));
	addChild(createScrew<ScrewSilver>(Vec(box.size.x - 30, 0)));
	addChild(createScrew<ScrewSilver>(Vec(15, 365)));
	addChild(createScrew<ScrewSilver>(Vec(box.size.x - 30, 365)));

	// generated by svg_widgets.rb
	auto delayParamPosition = Vec(27.08, 33.08);
	auto attackParamPosition = Vec(27.08, 89.08);
	auto decayParamPosition = Vec(27.08, 145.08);
	auto sustainParamPosition = Vec(27.08, 201.08);
	auto releaseParamPosition = Vec(27.08, 257.08);
	auto holdParamPosition = Vec(82.38, 313.08);
	auto attackShapeParamPosition = Vec(77.02, 124.02);
	auto decayShapeParamPosition = Vec(77.02, 180.52);
	auto releaseShapeParamPosition = Vec(77.02, 292.52);
	auto triggerParamPosition = Vec(90.04, 43.04);
	auto modeParamPosition = Vec(120.0, 95.0);
	auto loopParamPosition = Vec(120.0, 145.0);
	auto speedParamPosition = Vec(20.0, 321.0);
	auto retriggerParamPosition = Vec(55.0, 321.0);

	auto delayInputPosition = Vec(152.0, 40.0);
	auto attackInputPosition = Vec(152.0, 96.0);
	auto decayInputPosition = Vec(152.0, 152.0);
	auto sustainInputPosition = Vec(152.0, 208.0);
	auto releaseInputPosition = Vec(152.0, 264.0);
	auto holdInputPosition = Vec(152.0, 320.0);
	auto triggerInputPosition = Vec(115.0, 40.0);

	auto delayOutputPosition = Vec(189.0, 40.0);
	auto attackOutputPosition = Vec(189.0, 96.0);
	auto decayOutputPosition = Vec(189.0, 152.0);
	auto sustainOutputPosition = Vec(189.0, 208.0);
	auto releaseOutputPosition = Vec(189.0, 264.0);
	auto envOutputPosition = Vec(115.0, 191.0);
	auto invOutputPosition = Vec(115.0, 228.0);
	auto triggerOutputPosition = Vec(115.0, 265.0);

	auto delayLightPosition = Vec(12.0, 76.0);
	auto attackLightPosition = Vec(12.0, 123.0);
	auto decayLightPosition = Vec(12.0, 179.0);
	auto sustainLightPosition = Vec(12.0, 235.0);
	auto releaseLightPosition = Vec(12.0, 291.0);
	auto attackShape1LightPosition = Vec(77.0, 96.0);
	auto attackShape2LightPosition = Vec(77.0, 106.0);
	auto attackShape3LightPosition = Vec(77.0, 116.0);
	auto decayShape1LightPosition = Vec(77.0, 152.5);
	auto decayShape2LightPosition = Vec(77.0, 162.5);
	auto decayShape3LightPosition = Vec(77.0, 172.5);
	auto releaseShape1LightPosition = Vec(77.0, 264.5);
	auto releaseShape2LightPosition = Vec(77.0, 274.5);
	auto releaseShape3LightPosition = Vec(77.0, 284.5);
	// end generated by svg_widgets.rb

	addParam(createParam<Knob38>(delayParamPosition, module, DADSRHPlus::DELAY_PARAM, 0.0, 1.0, 0.0));
	addParam(createParam<Knob38>(attackParamPosition, module, DADSRHPlus::ATTACK_PARAM, 0.0, 1.0, 0.12));
	addParam(createParam<Knob38>(decayParamPosition, module, DADSRHPlus::DECAY_PARAM, 0.0, 1.0, 0.32));
	addParam(createParam<Knob38>(sustainParamPosition, module, DADSRHPlus::SUSTAIN_PARAM, 0.0, 1.0, 0.5));
	addParam(createParam<Knob38>(releaseParamPosition, module, DADSRHPlus::RELEASE_PARAM, 0.0, 1.0, 0.32));
	addParam(createParam<Knob38>(holdParamPosition, module, DADSRHPlus::HOLD_PARAM, 0.0, 1.0, 0.45));
	addParam(createParam<StatefulButton9>(attackShapeParamPosition, module, DADSRHPlus::ATTACK_SHAPE_PARAM, 1.0, 3.0, 1.0));
	addParam(createParam<StatefulButton9>(decayShapeParamPosition, module, DADSRHPlus::DECAY_SHAPE_PARAM, 1.0, 3.0, 1.0));
	addParam(createParam<StatefulButton9>(releaseShapeParamPosition, module, DADSRHPlus::RELEASE_SHAPE_PARAM, 1.0, 3.0, 1.0));
	addParam(createParam<Button18>(triggerParamPosition, module, DADSRHPlus::TRIGGER_PARAM, 0.0, 1.0, 0.0));
	addParam(createParam<SliderSwitch2State14>(modeParamPosition, module, DADSRHPlus::MODE_PARAM, 0.0, 1.0, 1.0));
	addParam(createParam<SliderSwitch2State14>(loopParamPosition, module, DADSRHPlus::LOOP_PARAM, 0.0, 1.0, 1.0));
	addParam(createParam<SliderSwitch2State14>(speedParamPosition, module, DADSRHPlus::SPEED_PARAM, 0.0, 1.0, 1.0));
	addParam(createParam<SliderSwitch2State14>(retriggerParamPosition, module, DADSRHPlus::RETRIGGER_PARAM, 0.0, 1.0, 1.0));

	addInput(createInput<Port24>(delayInputPosition, module, DADSRHPlus::DELAY_INPUT));
	addInput(createInput<Port24>(attackInputPosition, module, DADSRHPlus::ATTACK_INPUT));
	addInput(createInput<Port24>(decayInputPosition, module, DADSRHPlus::DECAY_INPUT));
	addInput(createInput<Port24>(sustainInputPosition, module, DADSRHPlus::SUSTAIN_INPUT));
	addInput(createInput<Port24>(releaseInputPosition, module, DADSRHPlus::RELEASE_INPUT));
	addInput(createInput<Port24>(holdInputPosition, module, DADSRHPlus::HOLD_INPUT));
	addInput(createInput<Port24>(triggerInputPosition, module, DADSRHPlus::TRIGGER_INPUT));

	addOutput(createOutput<Port24>(delayOutputPosition, module, DADSRHPlus::DELAY_OUTPUT));
	addOutput(createOutput<Port24>(attackOutputPosition, module, DADSRHPlus::ATTACK_OUTPUT));
	addOutput(createOutput<Port24>(decayOutputPosition, module, DADSRHPlus::DECAY_OUTPUT));
	addOutput(createOutput<Port24>(sustainOutputPosition, module, DADSRHPlus::SUSTAIN_OUTPUT));
	addOutput(createOutput<Port24>(releaseOutputPosition, module, DADSRHPlus::RELEASE_OUTPUT));
	addOutput(createOutput<Port24>(envOutputPosition, module, DADSRHPlus::ENV_OUTPUT));
	addOutput(createOutput<Port24>(invOutputPosition, module, DADSRHPlus::INV_OUTPUT));
	addOutput(createOutput<Port24>(triggerOutputPosition, module, DADSRHPlus::TRIGGER_OUTPUT));

	addChild(createLight<TinyLight<GreenLight>>(delayLightPosition, module, DADSRHPlus::DELAY_LIGHT));
	addChild(createLight<TinyLight<GreenLight>>(attackLightPosition, module, DADSRHPlus::ATTACK_LIGHT));
	addChild(createLight<TinyLight<GreenLight>>(decayLightPosition, module, DADSRHPlus::DECAY_LIGHT));
	addChild(createLight<TinyLight<GreenLight>>(sustainLightPosition, module, DADSRHPlus::SUSTAIN_LIGHT));
	addChild(createLight<TinyLight<GreenLight>>(releaseLightPosition, module, DADSRHPlus::RELEASE_LIGHT));
	addChild(createLight<TinyLight<GreenLight>>(attackShape1LightPosition, module, DADSRHPlus::ATTACK_SHAPE1_LIGHT));
	addChild(createLight<TinyLight<GreenLight>>(attackShape2LightPosition, module, DADSRHPlus::ATTACK_SHAPE2_LIGHT));
	addChild(createLight<TinyLight<GreenLight>>(attackShape3LightPosition, module, DADSRHPlus::ATTACK_SHAPE3_LIGHT));
	addChild(createLight<TinyLight<GreenLight>>(decayShape1LightPosition, module, DADSRHPlus::DECAY_SHAPE1_LIGHT));
	addChild(createLight<TinyLight<GreenLight>>(decayShape2LightPosition, module, DADSRHPlus::DECAY_SHAPE2_LIGHT));
	addChild(createLight<TinyLight<GreenLight>>(decayShape3LightPosition, module, DADSRHPlus::DECAY_SHAPE3_LIGHT));
	addChild(createLight<TinyLight<GreenLight>>(releaseShape1LightPosition, module, DADSRHPlus::RELEASE_SHAPE1_LIGHT));
	addChild(createLight<TinyLight<GreenLight>>(releaseShape2LightPosition, module, DADSRHPlus::RELEASE_SHAPE2_LIGHT));
	addChild(createLight<TinyLight<GreenLight>>(releaseShape3LightPosition, module, DADSRHPlus::RELEASE_SHAPE3_LIGHT));
}
