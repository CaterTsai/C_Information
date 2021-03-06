#pragma once

#include "constParameter.h"
#include "ofxXmlSettings.h"
class lightMesh
{
public:

	void init(int w, int h, int cols, int rows);
	
	void updateVector(int dx, int dy);
	void drawLight(int x, int y);
	void drawPoint(int x, int y);

	void loadConfig();
	void saveConfig();
	
	vector<ofVec2f> getPath(int sIdx, int eIdx);

	void editMode();

	void keyPressed(ofKeyEventArgs& e);
	void keyReleased(ofKeyEventArgs& e) {};

private:
	bool _editMode;
	int _editIdx;
	ofMesh _mesh;
	int _colNum, _rowNum;

//-------------------
//Singleton
//-------------------
private:
	lightMesh()
		:_colNum(0)
		, _rowNum(0)
		, _editMode(false)
	{}
	~lightMesh()
	{
		lightMesh::Destroy();
	}
	lightMesh(lightMesh const&);
	void operator=(lightMesh const&);

public:
	static lightMesh* GetInstance();
	static void Destroy();

private:
	static lightMesh *pInstance;

};