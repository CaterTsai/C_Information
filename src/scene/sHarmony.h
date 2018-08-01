#pragma once

#include "sBase.h"

class sHarmony : public sBase
{
private:
	struct colorSet
	{
		colorSet(eCubeType t, int i)
			:type(t)
			, index(i)
		{}
		eCubeType type;
		int index;
	};

public:
	sHarmony()
		:sBase(eSHarmony)
	{
		initRGBTeam();
	}

	void update(float delta) override 
	{
		if (!_isStart)
		{
			return;
		}
		
		if(_eMode == eClimb)
		{
			_timer -= delta;
			if (_timer < 0)
			{
				climb();
			}
		}
	}
	void drawMsg(ofVec2f pos) override
	{
		ostringstream ss;
		ss << "Harmony\n";
		ss << "1:Close\n";
		ss << "2:SingleBreathRandom\n";
		ss << "3:RedGreenCross\n";
		ss << "4:RGBTeamOn\n";
		ss << "5:RGBTeamBreath\n";
		ss << "6:RGBTeamFlash\n";
		ss << "7:Climb\n";
		ss << "8:RGBOn\n";
		ofDrawBitmapStringHighlight(ss.str(), pos);
	}

	void start() override
	{
		_isStart = true;
		_RGFlag = false;
		_teamFlag = 0;
		_team1 = _team2 = _team1Id = _team2Id = 0;
		cubeMgr::GetInstance()->allClose(1.0);
		_eMode = eClose;
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
				_eMode = eSingleBreathRandom;
				singleBreathRandom();
				break;
			}
			case eCtrl_ViewTrigger3:
			{
				_eMode = eRedGreenCross;
				redGreenCross();
				break;
			}
			case eCtrl_ViewTrigger4:
			{
				_eMode = eRGBTeamOn;
				rgbTeamOn();
				break;
			}
			case eCtrl_ViewTrigger5:
			{
				_eMode = eRGBTeamBreath;
				rgbTeamBreath();
				break;
			}
			case eCtrl_ViewTrigger6:
			{
				_eMode = eRGBTeamFlash;
				rgbTeamFlash();
				break;
			}
			case eCtrl_ViewTrigger7:
			{
				_eMode = eClimb;
				_climbIdx = 0;
				climb();
				break;
			}
			case eCtrl_ViewTrigger8:
			{
				rgbOn();
				_eMode = eRGBOn;
				break;
			}
			}
		}
	};

private:
	void initRGBTeam()
	{
		//Red
		_colorSet[0].push_back(colorSet(eCubeOne, 1));
		_colorSet[0].push_back(colorSet(eCubeThree, 1));

		//Green
		_colorSet[1].push_back(colorSet(eCubeTwo, 1));
		_colorSet[1].push_back(colorSet(eCubeFour, 1));

		//Blue
		_colorSet[2].push_back(colorSet(eCubeOne, 0));
		_colorSet[2].push_back(colorSet(eCubeTwo, 0));
		_colorSet[2].push_back(colorSet(eCubeThree, 0));
		_colorSet[2].push_back(colorSet(eCubeFour, 0));
	}

	void singleBreathRandom()
	{
		_timer = ofRandom(2.0f, 2.5f);
		int c = rand() % cCubeNum;
		int l = rand() % 2;
		cubeMgr::GetInstance()->chagneColorType((eCubeType)c, l, eColorType::eCT_Breathe, _timer, false);
	}

	void redGreenCross()
	{
		if (_RGFlag)
		{
			//Red
			cubeMgr::GetInstance()->chagneColorType(eCubeType::eCubeOne, 1, eColorType::eCT_Off);
			cubeMgr::GetInstance()->chagneColorType(eCubeType::eCubeThree, 1, eColorType::eCT_Off);

			//Green
			cubeMgr::GetInstance()->chagneColorType(eCubeType::eCubeTwo, 1, eColorType::eCT_On, 255.0);
			cubeMgr::GetInstance()->chagneColorType(eCubeType::eCubeFour, 1, eColorType::eCT_On, 255.0);
		}
		else
		{
			//Red
			cubeMgr::GetInstance()->chagneColorType(eCubeType::eCubeOne, 1, eColorType::eCT_On, 255.0);
			cubeMgr::GetInstance()->chagneColorType(eCubeType::eCubeThree, 1, eColorType::eCT_On, 255.0);

			//Green
			cubeMgr::GetInstance()->chagneColorType(eCubeType::eCubeTwo, 1, eColorType::eCT_Off);
			cubeMgr::GetInstance()->chagneColorType(eCubeType::eCubeFour, 1, eColorType::eCT_Off);
		}
		_RGFlag ^= true;
	}

	void rgbTeamOn()
	{	
		//Off
		auto before = _colorSet[_team1][_team1Id];
		cubeMgr::GetInstance()->chagneColorType(before.type, before.index, eColorType::eCT_Off);
		before = _colorSet[_team2][_team2Id];
		cubeMgr::GetInstance()->chagneColorType(before.type, before.index, eColorType::eCT_Off);

		_team1 = _teamFlag;
		_team2 = (_teamFlag + 1) % 3;
		_team1Id = rand() % _colorSet[_team1].size();
		_team2Id = rand() % _colorSet[_team2].size();

		//On
		auto after = _colorSet[_team1][_team1Id];
		cubeMgr::GetInstance()->chagneColorType(after.type, after.index, eColorType::eCT_On, 255.0);
		after = _colorSet[_team2][_team2Id];
		cubeMgr::GetInstance()->chagneColorType(after.type, after.index, eColorType::eCT_On, 255.0);

		_teamFlag = (_teamFlag + 1) % 3;
	}

	void rgbTeamBreath()
	{
		_team1 = _teamFlag;
		_team2 = (_teamFlag + 1) % 3;
		_team1Id = rand() % _colorSet[_team1].size();
		_team2Id = rand() % _colorSet[_team2].size();

		//On
		auto after = _colorSet[_team1][_team1Id];
		cubeMgr::GetInstance()->chagneColorType(after.type, after.index, eColorType::eCT_Breathe, 2.0, false);
		after = _colorSet[_team2][_team2Id];
		cubeMgr::GetInstance()->chagneColorType(after.type, after.index, eColorType::eCT_Breathe, 2.0, false);

		_teamFlag = (_teamFlag + 1) % 3;
	}

	void rgbTeamFlash()
	{
		_team1 = _teamFlag;
		_team2 = (_teamFlag + 1) % 3;
		_team1Id = rand() % _colorSet[_team1].size();
		_team2Id = rand() % _colorSet[_team2].size();

		//On
		auto after = _colorSet[_team1][_team1Id];
		cubeMgr::GetInstance()->chagneColorType(after.type, after.index, eColorType::eCT_Flash, 2.0, false);
		after = _colorSet[_team2][_team2Id];
		cubeMgr::GetInstance()->chagneColorType(after.type, after.index, eColorType::eCT_Flash, 2.0, false);

		_teamFlag = (_teamFlag + 1) % 3;
	}

	void climb()
	{
		cubeMgr::GetInstance()->chagneColorType((eCubeType)_climbIdx, rand() % 2, eColorType::eCT_OnAndFadeout, 1.5, false);
		_climbIdx = (_climbIdx + 1) % cCubeNum;
		_timer = 1.0;
	}

	void rgbOn()
	{
		for (auto& iter : _colorSet)
		{
			for (auto& color : iter)
			{
				cubeMgr::GetInstance()->chagneColorType((eCubeType)color.type, color.index, eColorType::eCT_FadeIn, 1.0);
			}
		}
	}

private:
	enum eMode {
		eClose = 0
		, eSingleBreathRandom
		, eRedGreenCross
		, eRGBTeamOn
		, eRGBTeamBreath
		, eRGBTeamFlash
		, eClimb
		, eRGBOn
	}_eMode;

	array<vector<colorSet>, 3> _colorSet;
	
	bool _RGFlag;
	int _teamFlag;
	int _team1, _team2, _team1Id, _team2Id;
	int _climbIdx;
	float _timer;
};
