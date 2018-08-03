#pragma once

#include "constParameter.h"
#include "ctrlMap.h"
#include "midiCtrl.h"
#include "lightMesh.h"
#include "moveLight.h"
#include "ofxAnimatableFloat.h"

class ofProjectionApp : public ofBaseApp, public ofxMidiListener
{
public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void newMidiMessage(ofxMidiMessage& msg) override;

private:
	float _timer;
	ofxAnimatableFloat _colorR;
	ofColor _lightColor;
	int _alpha;

	bool _edit;
	
};