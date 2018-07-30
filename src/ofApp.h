#pragma once

#include "constParameter.h"
#include "cubeMgr.h"
#include "lightMesh.h"
#include "sceneMgr.h"



class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void control(eCtrlType ctrl, int value = cMidiButtonPress);
private:
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

#pragma region lightMesh
public:
	void initLightMesh();
private:
	lightMesh _lightMesh;
#pragma endregion

};
