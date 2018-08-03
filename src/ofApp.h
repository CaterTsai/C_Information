#pragma once

#include "constParameter.h"
#include "cubeMgr.h"
#include "lightMesh.h"
#include "moveLight.h"
#include "sceneMgr.h"
#include "midiCtrl.h"


class ofApp : public ofBaseApp, public ofxMidiListener {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void control(eCtrlType ctrl, int value = cMidiButtonPress);
private:
	bool _showMsg;
	ofEasyCam _cam;
	float _mainTimer;

#pragma region SenderMgr
public:	
	void initSenderMgr();
#pragma endregion

#pragma region Scene
private:
	void initScene();
	
private:
	bool _isStart;
	vector<ofPtr<sBase>> _sceneMgr;
	eSType _nowScene;
#pragma endregion
	
#pragma region CubeMgr
public:
	void initCubeMgr();
#pragma endregion

//Midi
public:
	void updateMidi();
	void newMidiMessage(ofxMidiMessage& msg) override;

private:
	struct midiCtrlData
	{
		eCtrlType type;
		int value;
	};
	list<midiCtrlData> _midiQueue;
};
