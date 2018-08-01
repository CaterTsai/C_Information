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
	void drawMsg(ofVec2f pos) override 
	{
		ostringstream ss;
		ss << "Idle\n";
		ofDrawBitmapStringHighlight(ss.str(), pos);
	}

	void start() override
	{
		_isStart = true;
		cubeMgr::GetInstance()->allClose(1.0);
		_timer = 1.0f;
	};
	void stop() override 
	{
		_isStart = false;
	};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override {};

private:
	void triggerLight()
	{
		_timer = ofRandom(3.0, 5.0);
		int c = rand() % cCubeNum;
		cubeMgr::GetInstance()->chagneColorType((eCubeType)c, 0, eColorType::eCT_Breathe, _timer * ofRandom(1.0, 1.2), false);

		_timer *= 2.0;
	}

private:
	
	float _timer;
};