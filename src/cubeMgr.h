#pragma once

#include "cubeUnit.h"
#include "senderMgr.h"

class cubeMgr
{
public:

	void add(eCubeType type, int size, ofVec3f pos, ofColor c1, ofColor c2, ofColor c3)
	{
		_cubeMgr.insert(make_pair(type, cubeUnit()));
		_cubeMgr[type].init(size, pos, c1, c2, c3);
	}
	void update(float delta)
	{
		for (auto& iter : _cubeMgr)
		{
			iter.second.update(delta);
			senderMgr::GetInstance()->send(iter.first, iter.second.getCubeValue());
		}
	}
	void draw()
	{
		ofPushStyle();
		for (auto& iter : _cubeMgr)
		{
			iter.second.draw();
		}
		ofPopStyle();
	}

	void chagneColorType(eCubeType cType, int id, eColorType colorType)
	{
		if (_cubeMgr.find(cType) != _cubeMgr.end())
		{
			_cubeMgr[cType].setType(id, colorType);
		}
	}

	void chagneIntensity(eCubeType type, int id, int intensity)
	{
		if (_cubeMgr.find(type) != _cubeMgr.end())
		{
			_cubeMgr[type].setIntensity(id, intensity);
		}
	}

	array<int, cColorNumEachUnit> getColor(eCubeType type)
	{
		array<int, cColorNumEachUnit> value;
		value[0] = _cubeMgr[type]._colorList[0].getIntensity();
		value[1] = _cubeMgr[type]._colorList[1].getIntensity();
		value[2] = _cubeMgr[type]._colorList[2].getIntensity();

		return value;
	}
private:
	map<eCubeType, cubeUnit> _cubeMgr;

//-------------------
//Singleton
//-------------------
private:
	cubeMgr()
	{
	};
	~cubeMgr()
	{
		cubeMgr::Destroy();
	}
	cubeMgr(cubeMgr const&);
	void operator=(cubeMgr const&);

public:
	static cubeMgr* GetInstance();
	static void Destroy();

private:
	static cubeMgr *pInstance;

};