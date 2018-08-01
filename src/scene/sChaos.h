#pragma once

#include "sBase.h"

class sChaos : public sBase
{
public:
	sChaos()
		:sBase(eSChaos)
	{}

	void update(float delta) override {}
	void drawMsg(ofVec2f pos) override
	{
		ostringstream ss;
		ss << "Chaos\n";
		ofDrawBitmapStringHighlight(ss.str(), pos);
	}

	void start() override 
	{
		_isStart = true;
		_eMode = eBlueYellowFlash;
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
				_eMode = eCubeRandom;
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
	void blueYellowFlash(){
		for (int i = 0; i < cCubeNum; i++)
		{
			cubeMgr::GetInstance()->chagneColorType((eCubeType)i, 0, eColorType::eCT_Flash, 0.5);
			cubeMgr::GetInstance()->chagneColorType((eCubeType)i, 2, eColorType::eCT_Flash, 0.5);
		}
	}

	void allRandom()
	{
		_timer = 1.0f;
	}

	void allFastFlash()
	{

	}

	void climbFast()
	{
		for (int i = 0; i < cColorNumEachUnit; i++)
		{
			cubeMgr::GetInstance()->chagneColorType((eCubeType)_climbIdx, i , eColorType::eCT_OnAndFadeout, 0.5, false);
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