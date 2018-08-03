#include "ofApp.h"
#include "senderMgr.h"
//--------------------------------------------------------------
void ofApp::setup() {

	ofBackground(0);
	ofSetFrameRate(60);
	ofSetWindowPosition(0, 0);
	initCubeMgr();
	initSenderMgr();
	initScene();

	midiCtrl::GetInstance()->init();
	midiCtrl::GetInstance()->addListener(this);

	_mainTimer = ofGetElapsedTimef();

	_showMsg = true;
}

//--------------------------------------------------------------
void ofApp::update() {
	float delta = ofGetElapsedTimef() - _mainTimer;
	_mainTimer += delta;
	cubeMgr::GetInstance()->update(delta);

	senderMgr::GetInstance()->update(delta);
	_sceneMgr[_nowScene]->update(delta);

	updateMidi();

	moveLight::GetInstance()->updateLight(delta);
	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw() {

	_cam.begin();
	cubeMgr::GetInstance()->draw();
	_cam.end();
	
	if (_showMsg)
	{
		ofSetColor(255);
		string state = +_isStart ? "Play" : "Stop";
		ofDrawBitmapStringHighlight("State :" + state, ofVec2f(0, 95));
		_sceneMgr[_nowScene]->drawMsg(ofVec2f(0, 110));
	}
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
	senderMgr::GetInstance()->addSender(eCubeType::eCubeOne, "127.0.0.1", 8888);
	senderMgr::GetInstance()->addSender(eCubeType::eCubeTwo, "127.0.0.1", 8888);
	senderMgr::GetInstance()->addSender(eCubeType::eCubeThree, "127.0.0.1", 8888);
	senderMgr::GetInstance()->addSender(eCubeType::eCubeFour, "127.0.0.1", 8888);

	//senderMgr::GetInstance()->addSender(eCubeType::eCubeOne, "192.168.1.200", 8888);
	//senderMgr::GetInstance()->addSender(eCubeType::eCubeTwo, "192.168.1.201", 8888);
	//senderMgr::GetInstance()->addSender(eCubeType::eCubeThree, "192.168.1.202", 8888);
	//senderMgr::GetInstance()->addSender(eCubeType::eCubeFour, "192.168.1.203", 8888);
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
	_isStart = false;
}

//--------------------------------------------------------------
void ofApp::initCubeMgr()
{
	cubeMgr::GetInstance()->add(
		eCubeType::eCubeOne,
		200,
		ofVec3f(0, -300, 0),
		ofColor(0, 0, 255),
		ofColor(255, 0, 0),
		ofColor(255, 255, 0)
	);

	cubeMgr::GetInstance()->add(
		eCubeType::eCubeTwo,
		200,
		ofVec3f(0, -100, 0),
		ofColor(0, 0, 255),
		ofColor(0, 255, 0),
		ofColor(255, 255, 0)
	);

	cubeMgr::GetInstance()->add(
		eCubeType::eCubeThree,
		200,
		ofVec3f(0, 100, 0),
		ofColor(0, 0, 255),
		ofColor(255, 0, 0),
		ofColor(255, 255, 0)
	);

	cubeMgr::GetInstance()->add(
		eCubeType::eCubeFour,
		200,
		ofVec3f(0, 300, 0),
		ofColor(0, 0, 255),
		ofColor(0, 255, 0),
		ofColor(255, 255, 0)
	);
}

//void ofApp::initLightMesh()
//{
//	lightMesh::GetInstance()->init(1920, 900, 8, 4);
//	_edit = false;
//}

//----------------------------------
void ofApp::updateMidi()
{
	for (int i = 0; i < _midiQueue.size(); i++)
	{
		auto ctrl = _midiQueue.begin();
		if (ctrl->type >= 0 && ctrl->type < eCtrl_GlobalNum)
		{
			control(ctrl->type, ctrl->value);
		}
		else
		{
			_sceneMgr[_nowScene]->control(ctrl->type, ctrl->value);
		}
		_midiQueue.pop_front();
	}
}

//----------------------------------
void ofApp::newMidiMessage(ofxMidiMessage & msg)
{
	if (msg.value == cMidiButtonPress)
	{
		midiCtrlData newCtrl;
		newCtrl.type = ctrlMap::GetInstance()->midi2Ctrl[msg.control];
		newCtrl.value = msg.value;
		_midiQueue.push_back(newCtrl);
	}

}