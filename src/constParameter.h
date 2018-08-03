#pragma once


#include "ofMain.h"
#define PROJECT_MODE
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

const int cTailWidthLimit = 2;
const float cTailAddTime = 0.05f;

const array<int, 8> cLightMeshStart = { 0, 1, 8, 9, 16, 17, 24, 25 };
const array<int, 2> cLightMeshEnd = { 7, 15 };
