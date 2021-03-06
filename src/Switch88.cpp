
#include "Switch88.hpp"

struct Switch88Widget : SwitchMatrixModuleWidget {
	static constexpr int hp = 22;

	Switch88Widget(Switch88* module) {
		setModule(module);
		box.size = Vec(RACK_GRID_WIDTH * hp, RACK_GRID_HEIGHT);
		setPanel(box.size, "Switch88");
		createScrews();

		// generated by svg_widgets.rb
		auto mix11ParamPosition = Vec(54.5, 33.0);
		auto mix21ParamPosition = Vec(54.5, 70.0);
		auto mix31ParamPosition = Vec(54.5, 107.0);
		auto mix41ParamPosition = Vec(54.5, 144.0);
		auto mix51ParamPosition = Vec(54.5, 181.0);
		auto mix61ParamPosition = Vec(54.5, 218.0);
		auto mix71ParamPosition = Vec(54.5, 255.0);
		auto mix81ParamPosition = Vec(54.5, 292.0);
		auto mix12ParamPosition = Vec(89.5, 33.0);
		auto mix22ParamPosition = Vec(89.5, 70.0);
		auto mix32ParamPosition = Vec(89.5, 107.0);
		auto mix42ParamPosition = Vec(89.5, 144.0);
		auto mix52ParamPosition = Vec(89.5, 181.0);
		auto mix62ParamPosition = Vec(89.5, 218.0);
		auto mix72ParamPosition = Vec(89.5, 255.0);
		auto mix82ParamPosition = Vec(89.5, 292.0);
		auto mix13ParamPosition = Vec(124.5, 33.0);
		auto mix23ParamPosition = Vec(124.5, 70.0);
		auto mix33ParamPosition = Vec(124.5, 107.0);
		auto mix43ParamPosition = Vec(124.5, 144.0);
		auto mix53ParamPosition = Vec(124.5, 181.0);
		auto mix63ParamPosition = Vec(124.5, 218.0);
		auto mix73ParamPosition = Vec(124.5, 255.0);
		auto mix83ParamPosition = Vec(124.5, 292.0);
		auto mix14ParamPosition = Vec(159.5, 33.0);
		auto mix24ParamPosition = Vec(159.5, 70.0);
		auto mix34ParamPosition = Vec(159.5, 107.0);
		auto mix44ParamPosition = Vec(159.5, 144.0);
		auto mix54ParamPosition = Vec(159.5, 181.0);
		auto mix64ParamPosition = Vec(159.5, 218.0);
		auto mix74ParamPosition = Vec(159.5, 255.0);
		auto mix84ParamPosition = Vec(159.5, 292.0);
		auto mix15ParamPosition = Vec(194.5, 33.0);
		auto mix25ParamPosition = Vec(194.5, 70.0);
		auto mix35ParamPosition = Vec(194.5, 107.0);
		auto mix45ParamPosition = Vec(194.5, 144.0);
		auto mix55ParamPosition = Vec(194.5, 181.0);
		auto mix65ParamPosition = Vec(194.5, 218.0);
		auto mix75ParamPosition = Vec(194.5, 255.0);
		auto mix85ParamPosition = Vec(194.5, 292.0);
		auto mix16ParamPosition = Vec(229.5, 33.0);
		auto mix26ParamPosition = Vec(229.5, 70.0);
		auto mix36ParamPosition = Vec(229.5, 107.0);
		auto mix46ParamPosition = Vec(229.5, 144.0);
		auto mix56ParamPosition = Vec(229.5, 181.0);
		auto mix66ParamPosition = Vec(229.5, 218.0);
		auto mix76ParamPosition = Vec(229.5, 255.0);
		auto mix86ParamPosition = Vec(229.5, 292.0);
		auto mix17ParamPosition = Vec(264.5, 33.0);
		auto mix27ParamPosition = Vec(264.5, 70.0);
		auto mix37ParamPosition = Vec(264.5, 107.0);
		auto mix47ParamPosition = Vec(264.5, 144.0);
		auto mix57ParamPosition = Vec(264.5, 181.0);
		auto mix67ParamPosition = Vec(264.5, 218.0);
		auto mix77ParamPosition = Vec(264.5, 255.0);
		auto mix87ParamPosition = Vec(264.5, 292.0);
		auto mix18ParamPosition = Vec(299.5, 33.0);
		auto mix28ParamPosition = Vec(299.5, 70.0);
		auto mix38ParamPosition = Vec(299.5, 107.0);
		auto mix48ParamPosition = Vec(299.5, 144.0);
		auto mix58ParamPosition = Vec(299.5, 181.0);
		auto mix68ParamPosition = Vec(299.5, 218.0);
		auto mix78ParamPosition = Vec(299.5, 255.0);
		auto mix88ParamPosition = Vec(299.5, 292.0);

		auto in1InputPosition = Vec(10.5, 30.0);
		auto in2InputPosition = Vec(10.5, 67.0);
		auto in3InputPosition = Vec(10.5, 104.0);
		auto in4InputPosition = Vec(10.5, 141.0);
		auto in5InputPosition = Vec(10.5, 178.0);
		auto in6InputPosition = Vec(10.5, 215.0);
		auto in7InputPosition = Vec(10.5, 252.0);
		auto in8InputPosition = Vec(10.5, 289.0);

		auto out1OutputPosition = Vec(51.5, 328.0);
		auto out2OutputPosition = Vec(86.5, 328.0);
		auto out3OutputPosition = Vec(121.5, 328.0);
		auto out4OutputPosition = Vec(156.5, 328.0);
		auto out5OutputPosition = Vec(191.5, 328.0);
		auto out6OutputPosition = Vec(226.5, 328.0);
		auto out7OutputPosition = Vec(261.5, 328.0);
		auto out8OutputPosition = Vec(296.5, 328.0);
		// end generated by svg_widgets.rb

		createSwitch<InvertingIndicatorButton18>(mix11ParamPosition, module, Switch88::MIX11_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix21ParamPosition, module, Switch88::MIX21_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix31ParamPosition, module, Switch88::MIX31_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix41ParamPosition, module, Switch88::MIX41_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix51ParamPosition, module, Switch88::MIX51_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix61ParamPosition, module, Switch88::MIX61_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix71ParamPosition, module, Switch88::MIX71_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix81ParamPosition, module, Switch88::MIX81_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix12ParamPosition, module, Switch88::MIX12_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix22ParamPosition, module, Switch88::MIX22_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix32ParamPosition, module, Switch88::MIX32_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix42ParamPosition, module, Switch88::MIX42_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix52ParamPosition, module, Switch88::MIX52_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix62ParamPosition, module, Switch88::MIX62_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix72ParamPosition, module, Switch88::MIX72_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix82ParamPosition, module, Switch88::MIX82_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix13ParamPosition, module, Switch88::MIX13_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix23ParamPosition, module, Switch88::MIX23_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix33ParamPosition, module, Switch88::MIX33_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix43ParamPosition, module, Switch88::MIX43_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix53ParamPosition, module, Switch88::MIX53_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix63ParamPosition, module, Switch88::MIX63_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix73ParamPosition, module, Switch88::MIX73_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix83ParamPosition, module, Switch88::MIX83_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix14ParamPosition, module, Switch88::MIX14_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix24ParamPosition, module, Switch88::MIX24_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix34ParamPosition, module, Switch88::MIX34_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix44ParamPosition, module, Switch88::MIX44_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix54ParamPosition, module, Switch88::MIX54_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix64ParamPosition, module, Switch88::MIX64_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix74ParamPosition, module, Switch88::MIX74_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix84ParamPosition, module, Switch88::MIX84_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix15ParamPosition, module, Switch88::MIX15_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix25ParamPosition, module, Switch88::MIX25_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix35ParamPosition, module, Switch88::MIX35_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix45ParamPosition, module, Switch88::MIX45_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix55ParamPosition, module, Switch88::MIX55_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix65ParamPosition, module, Switch88::MIX65_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix75ParamPosition, module, Switch88::MIX75_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix85ParamPosition, module, Switch88::MIX85_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix16ParamPosition, module, Switch88::MIX16_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix26ParamPosition, module, Switch88::MIX26_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix36ParamPosition, module, Switch88::MIX36_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix46ParamPosition, module, Switch88::MIX46_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix56ParamPosition, module, Switch88::MIX56_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix66ParamPosition, module, Switch88::MIX66_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix76ParamPosition, module, Switch88::MIX76_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix86ParamPosition, module, Switch88::MIX86_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix17ParamPosition, module, Switch88::MIX17_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix27ParamPosition, module, Switch88::MIX27_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix37ParamPosition, module, Switch88::MIX37_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix47ParamPosition, module, Switch88::MIX47_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix57ParamPosition, module, Switch88::MIX57_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix67ParamPosition, module, Switch88::MIX67_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix77ParamPosition, module, Switch88::MIX77_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix87ParamPosition, module, Switch88::MIX87_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix18ParamPosition, module, Switch88::MIX18_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix28ParamPosition, module, Switch88::MIX28_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix38ParamPosition, module, Switch88::MIX38_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix48ParamPosition, module, Switch88::MIX48_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix58ParamPosition, module, Switch88::MIX58_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix68ParamPosition, module, Switch88::MIX68_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix78ParamPosition, module, Switch88::MIX78_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix88ParamPosition, module, Switch88::MIX88_PARAM);

		addInput(createInput<Port24>(in1InputPosition, module, Switch88::IN1_INPUT));
		addInput(createInput<Port24>(in2InputPosition, module, Switch88::IN2_INPUT));
		addInput(createInput<Port24>(in3InputPosition, module, Switch88::IN3_INPUT));
		addInput(createInput<Port24>(in4InputPosition, module, Switch88::IN4_INPUT));
		addInput(createInput<Port24>(in5InputPosition, module, Switch88::IN5_INPUT));
		addInput(createInput<Port24>(in6InputPosition, module, Switch88::IN6_INPUT));
		addInput(createInput<Port24>(in7InputPosition, module, Switch88::IN7_INPUT));
		addInput(createInput<Port24>(in8InputPosition, module, Switch88::IN8_INPUT));

		addOutput(createOutput<Port24>(out1OutputPosition, module, Switch88::OUT1_OUTPUT));
		addOutput(createOutput<Port24>(out2OutputPosition, module, Switch88::OUT2_OUTPUT));
		addOutput(createOutput<Port24>(out3OutputPosition, module, Switch88::OUT3_OUTPUT));
		addOutput(createOutput<Port24>(out4OutputPosition, module, Switch88::OUT4_OUTPUT));
		addOutput(createOutput<Port24>(out5OutputPosition, module, Switch88::OUT5_OUTPUT));
		addOutput(createOutput<Port24>(out6OutputPosition, module, Switch88::OUT6_OUTPUT));
		addOutput(createOutput<Port24>(out7OutputPosition, module, Switch88::OUT7_OUTPUT));
		addOutput(createOutput<Port24>(out8OutputPosition, module, Switch88::OUT8_OUTPUT));
	}
};

Model* modelSwitch88 = createModel<Switch88, Switch88Widget>("Bogaudio-Switch88", "SWITCH88", "8x8 matrix mixer", "Mixer", "Polyphonic");
