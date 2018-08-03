#pragma once

#include "constParameter.h"

class moveLight
{
#pragma region Tail
	struct tailUnit {
		ofVec2f pos;
		ofVec2f decline[2];
		float lifeT;
	};

	class tail {
	public:
		tail();
		~tail();
		void set(float lifeT, float width, bool isDecline, float declineT);
		void update(float delta);
		void draw();
		void addPos(ofVec2f p);
		int getTailSize();

	private:
		bool _isDecline;
		list<tailUnit> _tailUnitList;
		ofMesh _tailMesh;
		float _tailLifeT;
		float _width, _declineT;
	};
#pragma endregion

#pragma region partical
	class partical
	{
	public:
		partical()
			:_isSet(false)
		{}

		partical(vector<ofVec2f>& path, float speed);

		void update(float delta);

	public:
		bool _isSet;
		int _index;
		ofVec2f _pos, _vec;
		vector<ofVec2f> _path;
		bool _isLife, _isNoTail;
		float _speed;
		tail _tail;

		float _timer;

	};
#pragma endregion
	
public:
	void updateLight(float delta);
	void drawLight(ofColor c);
	void addLight(vector<ofVec2f>& path, float speed);
	

private:
	void checkLight();
private:
	list<partical> _lightList;

//-------------------
//Singleton
//-------------------
private:
	moveLight() {};
	~moveLight()
	{
		moveLight::Destroy();
	}
	moveLight(moveLight const&);
	void operator=(moveLight const&);

public:
	static moveLight* GetInstance();
	static void Destroy();

private:
	static moveLight *pInstance;
};