#include "moveLight.h"


#pragma region Tail
//--------------------------------------
moveLight::tail::tail()
	:_width(10.0f)
	, _declineT(1.0f)
{
	_tailMesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_TRIANGLE_STRIP);

}

//--------------------------------------
moveLight::tail::~tail()
{
	_tailMesh.clear();
	_tailUnitList.clear();
}

//--------------------------------------
void moveLight::tail::set(float lifeT, float width, bool isDecline, float declineT)
{
	_tailLifeT = lifeT;
	_width = width;
	_isDecline = isDecline;
	_declineT = declineT;
}

//--------------------------------------
void moveLight::tail::update(float delta)
{
	if (_tailMesh.getNumVertices() < 2)
	{
		return;
	}

	if (_isDecline)
	{
		int index = 0;
		for (auto& iter : _tailUnitList)
		{
			auto p1 = _tailMesh.getVertex(index * 2);
			auto p2 = _tailMesh.getVertex(index * 2 + 1);
			p1 += delta * iter.decline[0];
			p2 += delta * iter.decline[1];

			auto check = (p2 - p1) * iter.decline[0];

			if (p1.distance(p2) > cTailWidthLimit && check.x > 0 && check.y > 0)
			{
				_tailMesh.setVertex(index * 2, p1);
				_tailMesh.setVertex(index * 2 + 1, p2);
			}
			index++;
		}

	}

	for (auto& iter : _tailUnitList)
	{
		iter.lifeT -= delta;
	}

	if (_tailUnitList.begin()->lifeT < 0.0f)
	{
		_tailUnitList.pop_front();
		_tailMesh.removeVertex(0);
		_tailMesh.removeVertex(0);
	}

}

//--------------------------------------
void moveLight::tail::draw()
{
	_tailMesh.draw();
}

//--------------------------------------
void moveLight::tail::addPos(ofVec2f p)
{
	tailUnit newTailUnit;
	newTailUnit.pos = p;
	newTailUnit.lifeT = _tailLifeT;

	if (_tailUnitList.size() == 0)
	{
		_tailUnitList.push_back(newTailUnit);
	}
	else
	{
		auto last = _tailUnitList.rbegin();
		ofVec2f v = newTailUnit.pos - last->pos;
		v.normalize();
		ofVec2f up, down;
		up = down = v;

		up.rotate(90);
		down.rotate(-90);

		ofVec2f pUp = newTailUnit.pos + (up * _width);
		ofVec2f pDown = newTailUnit.pos + (down * _width);

		newTailUnit.decline[0] = (down  * _width) / _declineT;
		newTailUnit.decline[1] = (up  * _width) / _declineT;

		if (_tailUnitList.size() == 1)
		{
			ofVec2f pFirstUp = last->pos + (up * _width);
			ofVec2f pFirstDown = last->pos + (down * _width);
			last->decline[0] = (down  * _width) / _declineT;
			last->decline[1] = (up  * _width) / _declineT;
			_tailMesh.addVertex(pFirstUp);
			_tailMesh.addVertex(pFirstDown);
		}
		_tailMesh.addVertex(pUp);
		_tailMesh.addVertex(pDown);
		_tailUnitList.push_back(newTailUnit);
	}
}

int moveLight::tail::getTailSize()
{
	return _tailUnitList.size();
}

#pragma endregion

#pragma region partical
//--------------------------------------------------------------
moveLight::partical::partical(vector<ofVec2f>& path, float speed)
	:_isSet(true)
	, _isLife(true)
	, _isNoTail(false)
{
	if (path.size() < 2)
	{
		_isLife = false;
		return;
	}
	_path = path;
	_pos = _path[0];
	_index = 1;
	_speed = speed;
	_vec = (_path[1] - _path[0]).normalized() * speed;
	float t = ((path.size() * 300) / speed);
	_tail.set(t * 0.1, 5.0, true, t * 0.2);
	_timer = cTailAddTime;
}

//--------------------------------------------------------------
void moveLight::partical::update(float delta)
{
	if (!_isLife && _isNoTail && !_isSet)
	{
		return;
	}
	
	if (!_isLife && !_isNoTail)
	{
		_isNoTail = (_tail.getTailSize() <= 1);
	}

	auto diff = _vec * delta;

	if (_pos.distance(_path[_index]) <= diff.length())
	{
		_pos = _path[_index];
		if ((_index + 1) == _path.size())
		{
			_isLife = false;
		}
		else
		{
			_index++;
			_vec = (_path[_index] - _pos).normalized() * _speed;
		}
	}
	else
	{
		_pos += diff;
	}

	_tail.update(delta);
	_timer -= delta;
	if (_isLife && _timer < 0.0f)
	{
		_timer = cTailAddTime;
		_tail.addPos(_pos);
	}
}


#pragma endregion

//--------------------------------------------------------------
void moveLight::updateLight(float delta)
{
	for (auto& iter : _lightList)
	{
		iter.update(delta);
	}

	checkLight();
}

//--------------------------------------------------------------
void moveLight::drawLight(ofColor c)
{
	for (auto& iter : _lightList)
	{
		ofSetColor(c);
		iter._tail.draw();
	}
}

//--------------------------------------------------------------
void moveLight::addLight(vector<ofVec2f>& path, float speed)
{
	_lightList.push_back(partical(path, speed));
}

//--------------------------------------------------------------
void moveLight::checkLight()
{
	_lightList.remove_if([](const partical & p)
	{
		return (!p._isLife && (p._isNoTail));
	});
}


//--------------------------------------------------------------
moveLight* moveLight::pInstance = 0;
moveLight* moveLight::GetInstance()
{
	if (pInstance == 0)
	{
		pInstance = new moveLight();
	}
	return pInstance;
}

//--------------------------------------------------------------
void moveLight::Destroy()
{
	if (pInstance != 0)
	{
		delete pInstance;
	}
}


