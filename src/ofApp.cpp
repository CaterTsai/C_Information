#include "ofApp.h"
#include "senderMgr.h"
//--------------------------------------------------------------
void ofApp::setup(){

	ofBackground(0);
	ofSetFrameRate(60);

	initCubeMgr();
	initSenderMgr();

	_mainTimer = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::update(){
	float delta = ofGetElapsedTimef() - _mainTimer;
	_mainTimer += delta;
	_cubeMgr.update(delta);

	senderMgr::GetInstance()->update(delta);
}

//--------------------------------------------------------------
void ofApp::draw(){

	_cam.begin();
	_cubeMgr.draw();
	_cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	switch (key)
	{
	case 'q':
	{
		_cubeMgr.chagneColorType(eCubeType::eCubeOne, 0, eColorType::eCT_Off);
		break;
	}
	case 'w':
	{
		_cubeMgr.chagneColorType(eCubeType::eCubeOne, 0, eColorType::eCT_OnLow);
		_cubeMgr.chagneColorType(eCubeType::eCubeOne, 1, eColorType::eCT_OnMiddles);
		_cubeMgr.chagneColorType(eCubeType::eCubeOne, 2, eColorType::eCT_OnHigh);
		break;
	}
	case 'e':
	{
		_cubeMgr.chagneColorType(eCubeType::eCubeOne, 0, eColorType::eCT_OnMiddles);
		break;
	}
	case 'r':
	{
		_cubeMgr.chagneColorType(eCubeType::eCubeOne, 0, eColorType::eCT_OnHigh);
		break;
	}
	case 't':
	{
		_cubeMgr.chagneColorType(eCubeType::eCubeOne, 0, eColorType::eCT_BreatheSlow);
		break;
	}
	case 'y':
	{
		_cubeMgr.chagneColorType(eCubeType::eCubeOne, 0, eColorType::eCT_BreatheMiddle);
		break;
	}
	case 'u':
	{
		_cubeMgr.chagneColorType(eCubeType::eCubeOne, 0, eColorType::eCT_BreatheFast);
		break;
	}
	case 'i':
	{
		_cubeMgr.chagneColorType(eCubeType::eCubeOne, 0, eColorType::eCT_FlashSlow);
		break;
	}
	case 'o':
	{
		_cubeMgr.chagneColorType(eCubeType::eCubeOne, 0, eColorType::eCT_FlashFast);
		break;
	}
	}
}

//--------------------------------------------------------------
void ofApp::initSenderMgr()
{
	senderMgr::GetInstance()->addSender(eCubeType::eCubeOne, "192.168.1.131", 8888);
	senderMgr::GetInstance()->addSender(eCubeType::eCubeTwo, "127.0.0.1", 2233);
	senderMgr::GetInstance()->addSender(eCubeType::eCubeThree, "127.0.0.1", 2233);
	senderMgr::GetInstance()->addSender(eCubeType::eCubeFour, "127.0.0.1", 2233);
	
}

//--------------------------------------------------------------
void ofApp::initCubeMgr()
{
	_cubeMgr.add(
		eCubeType::eCubeOne, 
		200, 
		ofVec3f(0, -300, 0), 
		ofColor(255, 0, 0), 
		ofColor(255, 255, 0), 
		ofColor(255, 0, 255)
	);

	_cubeMgr.add(
		eCubeType::eCubeTwo,
		200,
		ofVec3f(0, -100, 0),
		ofColor(255, 0, 0),
		ofColor(255, 255, 0),
		ofColor(255, 0, 255)
	);

	_cubeMgr.add(
		eCubeType::eCubeThree,
		200,
		ofVec3f(0, 100, 0),
		ofColor(255, 0, 0),
		ofColor(255, 255, 0),
		ofColor(255, 0, 255)
	);

	_cubeMgr.add(
		eCubeType::eCubeFour,
		200,
		ofVec3f(0, 300, 0),
		ofColor(255, 0, 0),
		ofColor(255, 255, 0),
		ofColor(255, 0, 255)
	);
}

//--------------------------------------------------------------
void ofApp::drawCubeMgr()
{
	_cubeMgr.draw();
}
