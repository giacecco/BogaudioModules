#pragma once

#include "bogaudio.hpp"

extern Model* modelPolyMult;

namespace bogaudio {

struct PolyMult : BGModule {
	enum ParamsIds {
		CHANNELS_PARAM,
		NUM_PARAMS
	};

	enum InputsIds {
		CHANNELS_INPUT,
		IN_INPUT,
		NUM_INPUTS
	};

	enum OutputsIds {
		OUT1_OUTPUT,
		OUT2_OUTPUT,
		OUT3_OUTPUT,
		OUT4_OUTPUT,
		NUM_OUTPUTS
	};

	PolyMult() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS);
		configParam(CHANNELS_PARAM, 1.0f, 16.0f, 1.0f, "Poly channels");
	}

	void processChannel(const ProcessArgs& args, int c) override;
};

} // namespace bogaudio
