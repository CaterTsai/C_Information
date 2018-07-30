#include "ofApp.h"
#include "senderMgr.h"
//--------------------------------------------------------------
void ofApp::setup() {

	ofBackground(0);
	ofSetFrameRate(60);
	ofSetWindowPosition(0, 0);
	initCubeMgr();
	initSenderMgr();
	initLightMesh();
	initScene();
	_mainTimer = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::update() {
	float delta = ofGetElapsedTimef() - _mainTimer;
	_mainTimer += delta;
	cubeMgr::GetInstance()->update(delta);

	senderMgr::GetInstance()->update(delta);
	_sceneMgr[_nowScene]->update(delta);

	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw() {

	_cam.begin();
	cubeMgr::GetInstance()->draw();
	_cam.end();

	//_lightMesh.drawLight(0, 0);
	//_lightMesh.drawPoint(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	eCtrlType type = ctrlMap::GetInstance()->key2Ctrl[key];
	if (type >= 0 && type < eCtrl_GlobalNum)
	{
		control(type);
	}
	else
	{
		_sceneMgr[_nowScene]->control(type);
	}
}

//----------------------------------
void ofApp::control(eCtrlType ctrl, int value)
{
	switch (ctrl)
	{
	case eCtrl_Start:
	{
		if (value == cMidiButtonPress)
		{
			_sceneMgr[_nowScene]->start();
			_isStart = true;
		}
		break;
	}
	case eCtrl_Stop:
	{
		if (value == cMidiButtonPress)
		{
			_sceneMgr[_nowScene]->stop();
			_isStart = false;
		}
		break;
	}
	case eCtrl_NextScence:
	{
		if (value == cMidiButtonPress)
		{

			auto nextScene = (eSType)((_nowScene + 1) % eSTypeNum);
			if (_isStart)
			{
				_sceneMgr[_nowScene]->stop();
				_sceneMgr[nextScene]->start();
			}
			_nowScene = nextScene;
		}

		break;
	}
	case eCtrl_PrevScence:
	{
		if (value == cMidiButtonPress)
		{

			auto nextScene = (eSType)((_nowScene - 1) % eSTypeNum);
			if (nextScene < 0)
			{
				nextScene = (eSType)(eSTypeNum - 1);
			}
			if (_isStart)
			{
				_sceneMgr[_nowScene]->stop();
				_sceneMgr[nextScene]->start();
			}
			_nowScene = nextScene;
		}
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
void ofApp::initScene()
{
	_sceneMgr.push_back(ofPtr<sIdle>(new sIdle));
	_sceneMgr.push_back(ofPtr<sIntro>(new sIntro));
	_sceneMgr.push_back(ofPtr<sSimple>(new sSimple));
	_sceneMgr.push_back(ofPtr<sHarmony>(new sHarmony));
	_sceneMgr.push_back(ofPtr<sChaos>(new sChaos));
	_sceneMgr.push_back(ofPtr<sToBeContinued>(new sToBeContinued));
	_sceneMgr.push_back(ofPtr<sEnding>(new sEnding));

	_nowScene = eSIdle;
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

