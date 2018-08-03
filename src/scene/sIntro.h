#pragma once

#include "sBase.h"

class sIntro : public sBase
{
public:
	sIntro()
		:sBase(eSIntro)
	{}

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

	};
	void stop() override 
	{
		_isStart = false;
	};
	
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override 
	{

	};
};