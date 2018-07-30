#pragma once

#include "sBase.h"

class sIdle : public sBase
{
public:
	sIdle()
		:sBase(eSIdle)
	{}

	void update(float delta) override {}
	void drawMsg(ofVec2f pos) override {}

	void start() override
	{
		cubeMgr::GetInstance()->chagneColorType(eCubeOne, 0, eColorType::eCT_BreatheMiddle, false);
	};
	void stop() override {};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override {};
};