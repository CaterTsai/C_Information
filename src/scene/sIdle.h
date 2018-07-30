#pragma once

#include "sBase.h"

class sIdle : public sBase
{
public:
	sIdle()
		:sBase(eSIdle)
	{}

	void update(float delta) override 
	{
		if (_isStart) {
			_timer -= delta;
			if (_timer < 0.0f)
			{
				triggerLight();
			}
		}
		
	}
	void drawMsg(ofVec2f pos) override {}

	void start() override
	{
		_isStart = true;
		triggerLight();
	};
	void stop() override 
	{
		_isStart = false;
	};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override {};

private:
	void triggerLight()
	{
		_timer = ofRandom(1.0, 3.0);
		int c = rand() % cCubeNum;
		int l = rand() % cColorNumEachUnit;
		cubeMgr::GetInstance()->chagneColorType((eCubeType)c, l, eColorType::eCT_BreatheControl, _timer * ofRandom(1.0, 1.2), false);
		_timer *= 2;
	}

private:
	float _timer;
};