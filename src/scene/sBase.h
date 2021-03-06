#pragma once

#include "../constParameter.h"
#include "../cubeMgr.h"
#include "../midiCtrl.h"
#include "../ctrlMap.h"
#include "sType.h"
#include "cubeMgr.h"

class sBase
{
public:
	sBase(eSType type):
		_type(type)
		, _isStart(false)
	{}

	virtual void update(float delta) {}
	virtual void draw() {};
	virtual void drawMsg(ofVec2f pos) {}

	virtual void start() {};
	virtual void stop() {};
	virtual void control(eCtrlType ctrl, int value = cMidiButtonPress) {};

protected:
	eSType _type;
	bool _isStart;
};