#pragma once

#include "bogaudio.hpp"
#include "dsp/envelope.hpp"
#include "dsp/filter.hpp"
#include "dsp/oscillator.hpp"
#include "dsp/signal.hpp"

using namespace bogaudio::dsp;

extern Model* modelFMOp;

namespace bogaudio {

struct FMOp : BGModule {
	enum ParamsIds {
		RATIO_PARAM,
		FINE_PARAM,
		ATTACK_PARAM,
		DECAY_PARAM,
		SUSTAIN_PARAM,
		RELEASE_PARAM,
		DEPTH_PARAM,
		FEEDBACK_PARAM,
		LEVEL_PARAM,
		ENV_TO_LEVEL_PARAM,
		ENV_TO_FEEDBACK_PARAM,
		ENV_TO_DEPTH_PARAM,
		NUM_PARAMS
	};

	enum InputsIds {
		SUSTAIN_INPUT,
		DEPTH_INPUT,
		FEEDBACK_INPUT,
		LEVEL_INPUT,
		PITCH_INPUT,
		GATE_INPUT,
		FM_INPUT,
		NUM_INPUTS
	};

	enum OutputsIds {
		AUDIO_OUTPUT,
		NUM_OUTPUTS
	};

	enum LightsIds {
		ATTACK_LIGHT,
		DECAY_LIGHT,
		SUSTAIN_LIGHT,
		RELEASE_LIGHT,
		NUM_LIGHTS
	};

	static constexpr float amplitude = 5.0f;
	static constexpr int oversample = 8;
	static constexpr float oversampleMixIncrement = 0.01f;

	struct Engine {
		float feedback = 0.0f;
		float feedbackDelayedSample = 0.0f;
		float depth = 0.0f;
		float level = 0.0f;
		bool envelopeOn = false;
		float maxFrequency = 0.0f;
		float buffer[oversample];
		float oversampleMix = 0.0f;
		dsp::ADSR envelope;
		Phasor phasor;
		SineTableOscillator sineTable;
		CICDecimator decimator;
		Trigger gateTrigger;
		bogaudio::dsp::SlewLimiter feedbackSL;
		bogaudio::dsp::SlewLimiter depthSL;
		bogaudio::dsp::SlewLimiter levelSL;
		bogaudio::dsp::SlewLimiter sustainSL;
		Amplifier amplifier;

		Engine() : envelope(true) {}

		void reset();
		void sampleRateChange();
	};

	bool _linearLevel = false;
	bool _levelEnvelopeOn = false;
	bool _feedbackEnvelopeOn = false;
	bool _depthEnvelopeOn = false;
	int _attackLightSum;
	int _decayLightSum;
	int _sustainLightSum;
	int _releaseLightSum;
	Engine* _engines[maxChannels] {};

	struct RatioParamQuantity : ParamQuantity {
		float getDisplayValue() override;
		void setDisplayValue(float v) override;
	};

	struct LevelParamQuantity : AmpliferParamQuantity {
		bool isLinear() override;
	};

	FMOp() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam<RatioParamQuantity>(RATIO_PARAM, -1.0f, 1.0f, 0.0f, "Frequency ratio");
		configParam(FINE_PARAM, -1.0f, 1.0f, 0.0f, "Fine tune", " cents", 0.0f, 100.0f);
		configParam<EnvelopeSegmentParamQuantity>(ATTACK_PARAM, 0.0f, 1.0f, 0.141421f, "Attack", " s");
		configParam<EnvelopeSegmentParamQuantity>(DECAY_PARAM, 0.0f, 1.0f, 0.31623f, "Decay", " s");
		configParam(SUSTAIN_PARAM, 0.0f, 1.0f, 1.0f, "Sustain", "%", 0.0f, 100.0f);
		configParam<EnvelopeSegmentParamQuantity>(RELEASE_PARAM, 0.0f, 1.0f, 0.31623f, "Release", " s");
		configParam(DEPTH_PARAM, 0.0f, 1.0f, 0.0f, "FM depth", "%", 0.0f, 100.0f);
		configParam(FEEDBACK_PARAM, 0.0f, 1.0f, 0.0f, "Feedback", "%", 0.0f, 100.0f);
		configParam<LevelParamQuantity>(LEVEL_PARAM, 0.0f, 1.0f, 1.0f, "Level");
		configParam(ENV_TO_LEVEL_PARAM, 0.0f, 1.0f, 0.0f, "Level follows envelope");
		configParam(ENV_TO_FEEDBACK_PARAM, 0.0f, 1.0f, 0.0f, "Feedback follows envelope");
		configParam(ENV_TO_DEPTH_PARAM, 0.0f, 1.0f, 0.0f, "FM depth follows envelope");
	}

	void reset() override;
	void sampleRateChange() override;
	json_t* dataToJson() override;
	void dataFromJson(json_t* root) override;
	bool active() override;
	int channels() override;
	void addChannel(int c) override;
	void removeChannel(int c) override;
	void modulate() override;
	void modulateChannel(int c) override;
	void always(const ProcessArgs& args) override;
	void processChannel(const ProcessArgs& args, int c) override;
	void postProcess(const ProcessArgs& args) override;
};

} // namespace bogaudio
