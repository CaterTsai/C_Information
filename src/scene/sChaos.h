#pragma once

#include "sBase.h"

class sChaos : public sBase
{
public:
	sChaos()
		:sBase(eSChaos)
	{}

	void update(float delta) override
	{
		if (!_isStart)
		{
			return;
		}


		if (_timer > 0)
		{
			_timer -= delta;

			if (_timer < 0)
			{
				switch (_eMode)
				{
				case eClimbFast:
				{
					climbFast();
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
		ss << "Chaos\n";
		ss << "1:Close\n";
		ss << "2:eBlueYellowFlash\n";
		ss << "3:eAllRandom\n";
		ss << "4:eAllFastFlash\n";
		ss << "5:eClimbFast\n";
		ofDrawBitmapStringHighlight(ss.str(), pos);
	}

	void start() override
	{
		_isStart = true;
		_eMode = eBlueYellowFlash;
		blueYellowFlash();
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
				_eMode = eBlueYellowFlash;
				blueYellowFlash();
				break;
			}
			case eCtrl_ViewTrigger3:
			{
				_eMode = eAllRandom;
				allRandom();
				break;
			}
			case eCtrl_ViewTrigger4:
			{
				_eMode = eAllFastFlash;
				allFastFlash();
				break;
			}
			case eCtrl_ViewTrigger5:
			{
				_eMode = eClimbFast;
				climbFast();
				break;
			}
			}
		}
	};

private:
	void blueYellowFlash() {
		for (int i = 0; i < cCubeNum; i++)
		{
			cubeMgr::GetInstance()->chagneColorType((eCubeType)i, 0, eColorType::eCT_Flash, 0.5);
			cubeMgr::GetInstance()->chagneColorType((eCubeType)i, 2, eColorType::eCT_Flash, 0.5);
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

	void allFastFlash()
	{
		for (int i = 0; i < cCubeNum; i++)
		{
			for (int j = 0; j < cColorNumEachUnit; j++)
			{
				cubeMgr::GetInstance()->chagneColorType((eCubeType)i, j, eColorType::eCT_Flash, ofRandom(0.5, 2.0));
			}
		}
	}

	void climbFast()
	{
		for (int i = 0; i < cColorNumEachUnit; i++)
		{
			cubeMgr::GetInstance()->chagneColorType((eCubeType)_climbIdx, i, eColorType::eCT_OnAndFadeout, 0.5, false);
		}
		_climbIdx = (_climbIdx + 1) % cCubeNum;
		_timer = 0.2;
	}
private:
	enum eMode
	{
		eClose = 0,
		eBlueYellowFlash,
		eAllRandom,
		eAllFastFlash,
		eClimbFast
	}_eMode;

	int _climbIdx;
	float _timer;
};