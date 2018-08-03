#pragma once

#include "sBase.h"

class sToBeContinued : public sBase
{
public:
	sToBeContinued()
		:sBase(eSToBeContinued)
	{}

	void update(float delta) override 
	{
		if (!_isStart)
		{
			return;
		}

		if (_timer >= 0.0f)
		{
			_timer -= delta;

			if (_timer < 0.0f)
			{
				switch (_eMode)
				{
				case eRandomYellowBreath:
				{
					randomYellowBreathe();
					break;
				}
				case eClimbYellow:
				{
					climb();
					break;
				}
				case eAllRandom:
				{
					allRandom();
					break;
				}
				}
			}
		}
	}
	void drawMsg(ofVec2f pos) override 
	{
		ostringstream ss;
		ss << "To Be Continued\n";
		ss << "1:Close\n";
		ss << "2:Random Yellow Breath\n";
		ss << "3:Trigger Yellow Light\n";
		ss << "4:Climb Yellow\n";
		ss << "5:Trigger RGB\n";
		ss << "6:All Random\n";
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
		if (_isStart && value == cMidiButtonPress)
		{
			switch (ctrl)
			{
			case eCtrl_ViewTrigger1:
			{
				_eMode = eClose;
				cubeMgr::GetInstance()->allClose(1.0);
				break;
			}
			case eCtrl_ViewTrigger2:
			{
				_eMode = eRandomYellowBreath;
				randomYellowBreathe();
				break;
			}
			case eCtrl_ViewTrigger3:
			{
				_eMode = eTriggerYellowLight;
				triggerYellow();
				break;
			}
			case eCtrl_ViewTrigger4:
			{
				_eMode = eClimbYellow;
				_climbIdx = 0;
				climb();
				break;
			}
			case eCtrl_ViewTrigger5:
			{
				triggerRGB();
				break;
			}
			case eCtrl_ViewTrigger6:
			{
				_eMode = eAllRandom;
				allRandom();
				break;
			}
			}
		}
	};

private:
	void randomYellowBreathe()
	{
		_timer = ofRandom(3.0, 5.0);
		int c = rand() % cCubeNum;
		cubeMgr::GetInstance()->chagneColorType((eCubeType)c, 2, eColorType::eCT_Breathe, _timer * ofRandom(1.0, 1.2), false);

		_timer *= 2.0;
	}

	void triggerYellow()
	{
		for (int i = 0; i < cCubeNum; i++)
		{
			float time = ofRandom(5.0, 7.0);
			cubeMgr::GetInstance()->chagneColorType((eCubeType)i, 2, eColorType::eCT_OnAndFadeout, time, false);
		}
	}

	void climb()
	{
		cubeMgr::GetInstance()->chagneColorType((eCubeType)_climbIdx, 2, eColorType::eCT_OnAndFadeout, 0.5, false);
		_climbIdx = (_climbIdx + 1) % cCubeNum;
		_timer = 0.24;
	}

	void triggerRGB()
	{
		
		for (int i = 0; i < cCubeNum; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				if ((rand() % 10) <= 4)
				{
					cubeMgr::GetInstance()->chagneColorType((eCubeType)i, j, eColorType::eCT_OnAndFadeout, 0.5, false);
				}
			}
		}
	}

	void allRandom()
	{
		_timer = 1.0f;
		for (int i = 0; i < cCubeNum; i++)
		{
			for (int j = 0; j < cColorNumEachUnit; j++)
			{
				if ((rand() % 10) <= 6)
				{
					cubeMgr::GetInstance()->chagneColorType((eCubeType)i, j, eColorType::eCT_OnAndFadeout, 0.5, false);
				}
			}
		}
	}

private:
	enum eMode {
		eClose = 0
		, eRandomYellowBreath
		, eTriggerYellowLight
		, eClimbYellow
		, eTiggerRGB
		, eAllRandom
	}_eMode;

	float _timer;
	int _climbIdx;
};