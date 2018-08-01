#pragma once

#include "sBase.h"

class sIntro : public sBase
{
public:
	sIntro()
		:sBase(eSIntro)
	{}

	void update(float delta) override {}
	void drawMsg(ofVec2f pos) override 
	{
		ostringstream ss;
		ss << "Intro\n";
		ofDrawBitmapStringHighlight(ss.str(), pos);
	}

	void start() override 
	{
		_isStart = true;
		cubeMgr::GetInstance()->allClose(1.0);

		//for (int i = 0; i < 4; i++)
		//{
		//	for (int j = 0; j < 3; j++)
		//	{
		//		cubeMgr::GetInstance()->chagneColorType((eCubeType)i, j, eColorType::eCT_Breathe, ofRandom(1.0, 5.0));
		//	}
		//	
		//}
		
	};
	void stop() override 
	{
		_isStart = false;
	};
	
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override 
	{

	};
};