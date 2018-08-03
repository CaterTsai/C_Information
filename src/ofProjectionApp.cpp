#include "ofProjectionApp.h"

//--------------------------------------------------------------
void ofProjectionApp::setup()
{
	ofBackground(0);

	midiCtrl::GetInstance()->addListener(this);

	ofSetFrameRate(60);
	ofSetVerticalSync(true);

	_lightColor.set(0, 72, 193);
	_colorR.setDuration(20);
	_colorR.setRepeatType(AnimRepeat::LOOP_BACK_AND_FORTH);
	_colorR.animateFromTo(0, 255);

	lightMesh::GetInstance()->init(1920, 900, 8, 4);
	_edit = false;

	_timer = ofGetElapsedTimef();

}

//--------------------------------------------------------------
void ofProjectionApp::update()
{
	float delta = ofGetElapsedTimef() - _timer;
	_timer += delta;
	_colorR.update(delta);
	_lightColor.r = _colorR.getCurrentValue();

}

//--------------------------------------------------------------
void ofProjectionApp::draw()
{
	ofPushStyle();
	ofSetColor(255, _alpha);
	moveLight::GetInstance()->drawLight(_lightColor);

	ofPopStyle();

	if (_edit)
	{
		lightMesh::GetInstance()->drawPoint(0, 0);
		lightMesh::GetInstance()->drawLight(0, 0);
	}
}

//--------------------------------------------------------------
void ofProjectionApp::keyPressed(int key)
{
	if (key == 'e')
	{
		_edit ^= true;
		lightMesh::GetInstance()->editMode();
	}
}

//--------------------------------------------------------------
void ofProjectionApp::newMidiMessage(ofxMidiMessage & msg)
{
	auto type = ctrlMap::GetInstance()->midi2Ctrl[msg.control];
	if (type == eCtrl_ChangeProjectAlpha)
	{
		_alpha = ofMap(msg.value, 0, 127, 0, 255);
	}
}
