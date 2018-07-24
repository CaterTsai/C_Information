#pragma once

#include "constParameter.h"
#include "cubeMgr.h"

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);

private:
	ofEasyCam _cam;
	float _mainTimer;

#pragma region SenderMgr
public:	
	void initSenderMgr();
#pragma endregion


#pragma region CubeMgr
public:
	void initCubeMgr();
	void drawCubeMgr();
private:
	cubeMgr _cubeMgr;
#pragma endregion

	
};
