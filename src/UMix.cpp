
#include "UMix.hpp"

#define SUM "sum"
#define CVMODE "cv_mode"

json_t* UMix::dataToJson() {
	json_t* root = MatrixBaseModule::dataToJson();
	json_object_set_new(root, SUM, json_boolean(_sum));
	return root;
}

void UMix::dataFromJson(json_t* root) {
	MatrixBaseModule::dataFromJson(root);
	json_t* s = json_object_get(root, SUM);
	if (s) {
		_sum = json_is_true(s);
	}
}

bool UMix::active() {
	return outputs[OUT_OUTPUT].isConnected();
}

int UMix::channels() {
	return inputs[IN1_INPUT].getChannels();
}

void UMix::processChannel(const ProcessArgs& args, int c) {
	outputs[OUT_OUTPUT].setChannels(_channels);

	if (_sum) {
		float out = 0.0f;
		for (int i = 0; i < 8; ++i) {
			out += _inputGainLevel * inputs[IN1_INPUT + i].getPolyVoltage(c);
		}
		if (_clippingMode == HARD_CLIPPING) {
			outputs[OUT_OUTPUT].setVoltage(clamp(out, -12.0f, 12.0f), c);
		}
		else {
			outputs[OUT_OUTPUT].setVoltage(_saturator[c].next(out), c);
		}
	}
	else {
		float out = 0.0f;
		int active = 0;
		for (int i = 0; i < 8; ++i) {
			if (inputs[IN1_INPUT + i].isConnected()) {
				out += _inputGainLevel * inputs[IN1_INPUT + i].getPolyVoltage(c);
				++active;
			}
		}
		if (active > 0) {
			out /= (float)active;
			if (_clippingMode == HARD_CLIPPING) {
				outputs[OUT_OUTPUT].setVoltage(clamp(out, -12.0f, 12.0f), c);
			}
			else {
				outputs[OUT_OUTPUT].setVoltage(_saturator[c].next(out), c);
			}
		}
		else {
			outputs[OUT_OUTPUT].setVoltage(0.0f, c);
		}
	}
}

struct UMixWidget : MatrixBaseModuleWidget {
	static constexpr int hp = 3;

	UMixWidget(UMix* module) {
		setModule(module);
		box.size = Vec(RACK_GRID_WIDTH * hp, RACK_GRID_HEIGHT);

		{
			SvgPanel *panel = new SvgPanel();
			panel->box.size = box.size;
			panel->setBackground(APP->window->loadSvg(asset::plugin(pluginInstance, "res/UMix.svg")));
			addChild(panel);
		}

		addChild(createWidget<ScrewSilver>(Vec(0, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 15, 365)));

		// generated by svg_widgets.rb
		auto in1InputPosition = Vec(10.5, 23.0);
		auto in2InputPosition = Vec(10.5, 58.5);
		auto in3InputPosition = Vec(10.5, 94.0);
		auto in4InputPosition = Vec(10.5, 129.5);
		auto in5InputPosition = Vec(10.5, 165.0);
		auto in6InputPosition = Vec(10.5, 200.5);
		auto in7InputPosition = Vec(10.5, 236.0);
		auto in8InputPosition = Vec(10.5, 270.5);

		auto outOutputPosition = Vec(10.5, 302.0);
		// end generated by svg_widgets.rb

		addInput(createInput<Port24>(in1InputPosition, module, UMix::IN1_INPUT));
		addInput(createInput<Port24>(in2InputPosition, module, UMix::IN2_INPUT));
		addInput(createInput<Port24>(in3InputPosition, module, UMix::IN3_INPUT));
		addInput(createInput<Port24>(in4InputPosition, module, UMix::IN4_INPUT));
		addInput(createInput<Port24>(in5InputPosition, module, UMix::IN5_INPUT));
		addInput(createInput<Port24>(in6InputPosition, module, UMix::IN6_INPUT));
		addInput(createInput<Port24>(in7InputPosition, module, UMix::IN7_INPUT));
		addInput(createInput<Port24>(in8InputPosition, module, UMix::IN8_INPUT));

		addOutput(createOutput<Port24>(outOutputPosition, module, UMix::OUT_OUTPUT));
	}

	void appendContextMenu(Menu* menu) override {
		UMix* m = dynamic_cast<UMix*>(module);
		assert(m);
		MatrixBaseModuleWidget::appendContextMenu(menu);
		menu->addChild(new OptionMenuItem("Average", [m]() { return !m->_sum; }, [m]() { m->_sum = !m->_sum; }));
	}
};

Model* modelUMix = bogaudio::createModel<UMix, UMixWidget>("Bogaudio-UMix", "UMIX", "8-input unity mixer", "Mixer", "Polyphonic");
