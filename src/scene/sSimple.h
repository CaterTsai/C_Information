#pragma once

#include "sBase.h"

class sSimple : public sBase
{
public:
	sSimple()
		:sBase(eSSimple)
	{}

	void update(float delta) override {}
	void drawMsg(ofVec2f pos) override 
	{
		ostringstream ss;
		ss << "Simple\n";
		ss << "1: Trigger Blue Light\n";
		ofDrawBitmapStringHighlight(ss.str(), pos);
	}

	void start() override 
	{
		_isStart = true;
		cubeMgr::GetInstance()->allClose(1.0);
	};
	void stop() override 
	{
		_isStart = false;
	};

	void control(eCtrlType ctrl, int value = cMidiButtonPress) override 
	{
		if (value == cMidiButtonPress && ctrl == eCtrlType::eCtrl_ViewTrigger1)
		{
			triggerBlue();
		}
	};

private:
	void triggerBlue()
	{
		for (int i = 0; i < cCubeNum; i++)
		{
			float time = ofRandom(5.0, 7.0);
			cubeMgr::GetInstance()->chagneColorType((eCubeType)i, 0, eColorType::eCT_OnAndFadeout, time, false);
		}
	}

private:

	float _timer;
};
