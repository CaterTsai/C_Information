#pragma once

#include "constParameter.h"
#include "colorUnit.h"

class cubeUnit
{
public:
	cubeUnit(){}
	void init(int size, ofVec3f pos, ofColor c1, ofColor c2, ofColor c3)
	{
		_size = size;
		_pos = pos;
		_colorList[0].setColor(c1);
		_colorList[1].setColor(c2);
		_colorList[2].setColor(c3);
	}
	void update(float delta)
	{
		for (auto& iter : _colorList)
		{
			iter.update(delta);
		}
	}
	void draw()
	{
		ofPushMatrix();
		ofTranslate(_pos);
		ofPushStyle();
		{
			ofNoFill();
			ofSetLineWidth(3);
			ofSetColor(255);
			ofDrawBox(_size);

			ofFill();
			float dist = _size * 0.3f;
			float posX = -dist;
			for (auto& iter : _colorList)
			{
				ofSetColor(iter.getDisplayColor());
				ofDrawSphere(posX, 0, 0, _size * 0.1);
				posX += dist;
			}
		}
		ofPopStyle();
		ofPopMatrix();
	}
	void allClose(float t)
	{
		for (auto& iter : _colorList)
		{
			iter.setColorType(eColorType::eCT_FadeOut, false, t);
		}
	};
	void setType(int id, eColorType type, bool isLoop, float t)
	{
		if (id >= 0 && id < _colorList.size())
		{
			_colorList[id].setColorType(type, isLoop, t);
		}
	}
	void setIntensity(int id, int value)
	{
		int updateV = MAX(0, MIN(255, value));	
	}
	array<int, cColorNumEachUnit> getCubeValue()
	{
		array<int, cColorNumEachUnit> result;
		result[0] = _colorList[0].getIntensity();
		result[1] = _colorList[1].getIntensity();
		result[2] = _colorList[2].getIntensity();

		return result;
	}

public:	
	ofVec3f _pos;
	int _size;
	array<colorUnit, cColorNumEachUnit> _colorList;
};