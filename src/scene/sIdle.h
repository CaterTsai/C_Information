#pragma once

#include "sBase.h"
#include "lightMesh.h"
#include "moveLight.h"

class sIdle : public sBase
{
public:
	sIdle()
		:sBase(eSIdle)
		, _lightEnable(false)
	{}

	void update(float delta) override 
	{
		if (_isStart) {
			_timer -= delta;
			_lightTimer -= delta;


			if (_timer < 0.0f)
			{
				triggerLight();
			}

			if (_lightTimer < 0.0f)
			{
				addLight();
				
				_lightTimer = ofRandom(3.0f, 10.0f);
			}
		}
		
	}
	void drawMsg(ofVec2f pos) override 
	{
		ostringstream ss;
		ss << "Idle\n";
		ss << "1 : Enable/Disalbe Light\n";
		ofDrawBitmapStringHighlight(ss.str(), pos);
	}

	void start() override
	{
		_isStart = true;
		cubeMgr::GetInstance()->allClose(1.0);
		_timer = 1.0f;
		_lightTimer = 5.0f;
	};
	void stop() override 
	{
		_isStart = false;
	};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override 
	{
		if (_isStart && value == cMidiButtonPress)
		{
			if (ctrl == eCtrl_ViewTrigger1)
			{
				_lightEnable ^= true;
			}
		}
	};

private:
	void triggerLight()
	{
		_timer = ofRandom(3.0, 5.0);
		int c = rand() % cCubeNum;
		for (int i = 0; i < 3; i++)
		{
			cubeMgr::GetInstance()->chagneColorType((eCubeType)c, i, eColorType::eCT_Breathe, _timer * ofRandom(1.0, 1.2), false);
		}
		_timer *= 2.0;
	}

	void addLight()
	{
		int s = cLightMeshStart[rand() % cLightMeshStart.size()];
		int e = cLightMeshEnd[rand() % cLightMeshEnd.size()];
		moveLight::GetInstance()->addLight(lightMesh::GetInstance()->getPath(s, e), ofRandom(50, 300));
	}

private:
	bool _lightEnable;
	float _lightTimer;
	float _timer;
};