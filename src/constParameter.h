#pragma once


#include "ofMain.h"

enum eCubeType : int
{
	eCubeOne = 0,
	eCubeTwo, 
	eCubeThree,
	eCubeFour
};

const int cColorNumEachUnit = 3;
const int cCubeNum = 4;
const int cBlueIndex = 0;


const int cUdpSendLength = 4;
const char cUdpSendEnd = '\x01';
const float cUdpSendInterv = 1.0 / 10.0f; //10 fps
const int cUdpSendMax = 200;
const int cUdpSendMin = 0;


