#pragma once

#include "sBase.h"

class sSimple : public sBase
{
public:
	sSimple()
		:sBase(eSSimple)
	{}

	void update(float delta) override {}
	virtual void draw() override {};
	virtual void drawMsg(ofVec2f pos) override {}

	virtual void start() override {};
	virtual void stop() override {};
	virtual void control(eCtrlType ctrl, int value = cMidiButtonPress) override {};
};
