#include "ofApp.h"
#include "senderMgr.h"
//--------------------------------------------------------------
void ofApp::setup(){

	ofBackground(0);
	ofSetFrameRate(60);
	ofSetWindowPosition(0, 0);
	//initCubeMgr();
	//initSenderMgr();
	initLightMesh();

	_mainTimer = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::update(){
	float delta = ofGetElapsedTimef() - _mainTimer;
	_mainTimer += delta;
	cubeMgr::GetInstance()->update(delta);

	senderMgr::GetInstance()->update(delta);
}

//--------------------------------------------------------------
void ofApp::draw(){

	//_cam.begin();
	//cubeMgr::GetInstance()->draw();
	//_cam.end();

	_lightMesh.drawLight(0, 0);
	_lightMesh.drawPoint(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	switch (key)
	{
	case 'e':
	{
		//Edit Mode
		_lightMesh.editMode();
		break;
	}
	case 't':
	{
		auto r = _lightMesh.getPath(24, 7);
		
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
	cubeMgr::GetInstance()->add(
		eCubeType::eCubeOne, 
		200, 
		ofVec3f(0, -300, 0), 
		ofColor(255, 0, 0), 
		ofColor(255, 255, 0), 
		ofColor(255, 0, 255)
	);

	cubeMgr::GetInstance()->add(
		eCubeType::eCubeTwo,
		200,
		ofVec3f(0, -100, 0),
		ofColor(255, 0, 0),
		ofColor(255, 255, 0),
		ofColor(255, 0, 255)
	);

	cubeMgr::GetInstance()->add(
		eCubeType::eCubeThree,
		200,
		ofVec3f(0, 100, 0),
		ofColor(255, 0, 0),
		ofColor(255, 255, 0),
		ofColor(255, 0, 255)
	);

	cubeMgr::GetInstance()->add(
		eCubeType::eCubeFour,
		200,
		ofVec3f(0, 300, 0),
		ofColor(255, 0, 0),
		ofColor(255, 255, 0),
		ofColor(255, 0, 255)
	);
}

void ofApp::initLightMesh()
{
	_lightMesh.init(1920, 900, 8, 4);
}

