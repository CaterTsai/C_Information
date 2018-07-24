#include "ctrlMap.h"
#include "midiCtrl.h"

//--------------------------------------------------------------
void ctrlMap::initKey2Ctrl()
{
	key2Ctrl['s'] = eCtrl_Start;
	key2Ctrl['d'] = eCtrl_Stop;
	key2Ctrl['w'] = eCtrl_NextScence;
	key2Ctrl['q'] = eCtrl_PrevScence;

	key2Ctrl['y'] = eCtrl_Filter1;
	key2Ctrl['u'] = eCtrl_Filter2;
	key2Ctrl['i'] = eCtrl_Filter3;
	key2Ctrl['h'] = eCtrl_Filter4;
	key2Ctrl['j'] = eCtrl_Filter5;
	key2Ctrl['k'] = eCtrl_Filter6;
	key2Ctrl['n'] = eCtrl_Filter7;
	key2Ctrl['m'] = eCtrl_Filter8;
	key2Ctrl[','] = eCtrl_Filter9;
	key2Ctrl['.'] = eCtrl_DisableAllFilter;
	key2Ctrl['/'] = eCtrl_ChangeFilterTarget;

	key2Ctrl['['] = eCtrl_DisplayEach;
	key2Ctrl[']'] = eCtrl_DisplayGroup;
	key2Ctrl['v'] = eCtrl_ViewNext;
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
	midi2Ctrl[eMidiTriggerM5] = eCtrl_StopLight;
	midi2Ctrl[eMidiNextBtn] = eCtrl_NextScence;
	midi2Ctrl[eMidiPrevBtn] = eCtrl_PrevScence;

	midi2Ctrl[eMidiKnob8] = eCtrl_ChangeBPM;
	midi2Ctrl[eMidiSlider6] = eCtrl_ChangeColorR;
	midi2Ctrl[eMidiSlider7] = eCtrl_ChangeColorG;
	midi2Ctrl[eMidiSlider8] = eCtrl_ChangeColorB;
	midi2Ctrl[eMidiTriggerS5] = eCtrl_SetChangeColor;
	midi2Ctrl[eMidiKnob7] = eCtrl_ChangeProjectAlpha;

	midi2Ctrl[eMidiTriggerS6] = eCtrl_Filter1;
	midi2Ctrl[eMidiTriggerS7] = eCtrl_Filter2;
	midi2Ctrl[eMidiTriggerS8] = eCtrl_Filter3;
	midi2Ctrl[eMidiTriggerM6] = eCtrl_Filter4;
	midi2Ctrl[eMidiTriggerM7] = eCtrl_Filter5;
	midi2Ctrl[eMidiTriggerM8] = eCtrl_Filter6;
	midi2Ctrl[eMidiTriggerR6] = eCtrl_Filter7;
	midi2Ctrl[eMidiTriggerR7] = eCtrl_Filter8;
	midi2Ctrl[eMidiTriggerR8] = eCtrl_Filter9;
	midi2Ctrl[eMidiTrackPrev] = eCtrl_DisableAllFilter;
	midi2Ctrl[eMidiTrackNext] = eCtrl_ChangeFilterTarget;

	midi2Ctrl[eMidiForward] = eCtrl_DisplayEach;
	midi2Ctrl[eMidiBackward] = eCtrl_DisplayGroup;
	midi2Ctrl[eMidiSetBtn] = eCtrl_ViewNext;
	midi2Ctrl[eMidiTriggerS1] = eCtrl_ViewTrigger1;
	midi2Ctrl[eMidiTriggerS2] = eCtrl_ViewTrigger2;
	midi2Ctrl[eMidiTriggerS3] = eCtrl_ViewTrigger3;
	midi2Ctrl[eMidiTriggerM1] = eCtrl_ViewTrigger4;
	midi2Ctrl[eMidiTriggerM2] = eCtrl_ViewTrigger5;
	midi2Ctrl[eMidiTriggerM3] = eCtrl_ViewTrigger6;
	midi2Ctrl[eMidiTriggerR1] = eCtrl_ViewTrigger7;
	midi2Ctrl[eMidiTriggerR2] = eCtrl_ViewTrigger8;
	midi2Ctrl[eMidiTriggerR3] = eCtrl_ViewTrigger9;

	midi2Ctrl[eMidiSlider1] = eCtrl_ViewSlider1;
	midi2Ctrl[eMidiSlider2] = eCtrl_ViewSlider2;
	midi2Ctrl[eMidiSlider3] = eCtrl_ViewSlider3;
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