#include "ctrlMap.h"
#include "midiCtrl.h"

//--------------------------------------------------------------
void ctrlMap::initKey2Ctrl()
{
	key2Ctrl['q'] = eCtrl_Start;
	key2Ctrl['w'] = eCtrl_Stop;
	key2Ctrl['e'] = eCtrl_NextScence;
	key2Ctrl['r'] = eCtrl_PrevScence;

	key2Ctrl['1'] = eCtrl_ViewTrigger1;
	key2Ctrl['2'] = eCtrl_ViewTrigger2;
	key2Ctrl['3'] = eCtrl_ViewTrigger3;
	key2Ctrl['4'] = eCtrl_ViewTrigger4;
	key2Ctrl['5'] = eCtrl_ViewTrigger5;
	key2Ctrl['6'] = eCtrl_ViewTrigger6;
	key2Ctrl['7'] = eCtrl_ViewTrigger7;
	key2Ctrl['8'] = eCtrl_ViewTrigger8;
	key2Ctrl['9'] = eCtrl_ViewTrigger9;
}

//--------------------------------------------------------------
void ctrlMap::initMidi2Ctrl()
{
	midi2Ctrl[eMidiPlayBtn] = eCtrl_Start;
	midi2Ctrl[eMidiStopBtn] = eCtrl_Stop;
	midi2Ctrl[eMidiNextBtn] = eCtrl_NextScence;
	midi2Ctrl[eMidiPrevBtn] = eCtrl_PrevScence;


	midi2Ctrl[eMidiTriggerS1] = eCtrl_ViewTrigger1;
	midi2Ctrl[eMidiTriggerS2] = eCtrl_ViewTrigger2;
	midi2Ctrl[eMidiTriggerS3] = eCtrl_ViewTrigger3;
	midi2Ctrl[eMidiTriggerS4] = eCtrl_ViewTrigger4;

	midi2Ctrl[eMidiTriggerM1] = eCtrl_ViewTrigger5;
	midi2Ctrl[eMidiTriggerM2] = eCtrl_ViewTrigger6;
	midi2Ctrl[eMidiTriggerM3] = eCtrl_ViewTrigger7;
	midi2Ctrl[eMidiTriggerM4] = eCtrl_ViewTrigger8;

	midi2Ctrl[eMidiTriggerR1] = eCtrl_ViewTrigger9;
	midi2Ctrl[eMidiTriggerR2] = eCtrl_ViewTrigger10;
	midi2Ctrl[eMidiTriggerR3] = eCtrl_ViewTrigger11;
	midi2Ctrl[eMidiTriggerR4] = eCtrl_ViewTrigger12;

	midi2Ctrl[eMidiSlider1] = eCtrl_ViewKnob1;
	midi2Ctrl[eMidiSlider2] = eCtrl_ViewKnob2;
	midi2Ctrl[eMidiSlider3] = eCtrl_ViewKnob3;
}

//--------------------------------------------------------------
ctrlMap::ctrlMap()
{
	initKey2Ctrl();
	initMidi2Ctrl();
}

//--------------------------------------------------------------
ctrlMap* ctrlMap::pInstance = 0;
ctrlMap* ctrlMap::GetInstance()
{
	if (pInstance == 0)
	{
		pInstance = new ctrlMap();
	}
	return pInstance;
}

//--------------------------------------------------------------
void ctrlMap::Destroy()
{
	if (pInstance != 0)
	{
		delete pInstance;
	}
}