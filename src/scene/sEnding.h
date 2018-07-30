#pragma once

#include "sBase.h"

class sEnding : public sBase
{
public:
	sEnding()
		:sBase(eSEnding)
	{}

	void update(float delta) override {}
	virtual void drawMsg(ofVec2f pos) override {}

	virtual void start() override {};
	virtual void stop() override {};
	virtual void control(eCtrlType ctrl, int value = cMidiButtonPress) override {};
};

