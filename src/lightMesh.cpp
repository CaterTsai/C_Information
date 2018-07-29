#include "lightMesh.h"

//---------------------------------
void lightMesh::init(int w, int h, int cols, int rows)
{
	_mesh.clear();
	
	float uw = float(w) / float(cols - 1);
	float uh = float(h) / float(rows - 1);

	int posX, posY;
	for (int y = 0; y < rows; y++)
	{
		posY = y * uh;
		for (int x = 0; x < cols; x++)
		{
			posX = x * uw;
			_mesh.addVertex(ofVec2f(posX, posY));
		}
	}
	loadConfig();
	
	for (int y = 0; y < rows - 1 ; y++)
	{
		for (int x = 0; x < cols - 1; x++)
		{
			int lt = y * cols + x;
			int rt = lt + 1;
			int lb = lt + cols;
			int rb = lb + 1;

			_mesh.addTriangle(lt, rt, lb);
			_mesh.addTriangle(rt, rb, lb);
			
		}
	}
	_colNum = cols;
	_rowNum = rows;
}

//---------------------------------
void lightMesh::updateVector(int dx, int dy)
{
	auto p = _mesh.getVertex(_editIdx);
	p.x += dx;
	p.y += dy;
	_mesh.setVertex(_editIdx, p);
}

//---------------------------------
void lightMesh::drawLight(int x, int y)
{
	ofPushMatrix();
	ofTranslate(x, y);
	ofPushStyle();
	ofSetLineWidth(50);
	ofSetColor(0, 255, 0);
	_mesh.drawWireframe();

	ofPopStyle();
	ofPopMatrix();
}

//---------------------------------
void lightMesh::drawPoint(int x, int y)
{
	ofPushMatrix();
	ofTranslate(x, y);
	ofPushStyle();
	
	
	for (int i = 0; i < _mesh.getNumVertices(); i++)
	{
		auto pos = _mesh.getVertex(i);
		if (_editMode)
		{
			if (i == _editIdx)
			{
				ofSetColor(255, 0, 0);
			}
			else
			{
				ofSetColor(255, 255, 0);
			}
			ofDrawCircle(pos, 10);
		}
		else
		{
			ofSetColor(255, 255, 0);
			ofDrawCircle(pos, 10);
		}
		
	}

	ofPopStyle();
	ofPopMatrix();
}

//---------------------------------
void lightMesh::loadConfig()
{
	ofxXmlSettings xml;
	if (!xml.loadFile("_config.xml"))
	{
		ofLog(OF_LOG_NOTICE, "[loadConfig]Can't found config");
		return;
	}

	int numVertex = xml.getNumTags("vertex");
	if (numVertex != _mesh.getNumVertices())
	{
		ofLog(OF_LOG_NOTICE, "[loadConfig]Vertex not equal");
		return;
	}

	for (int i = 0; i < numVertex; i++)
	{
		ofPoint p;
		xml.pushTag("vertex", i);
		p.x = xml.getValue("X", 0);
		p.y = xml.getValue("Y", 0);

		_mesh.setVertex(i, p);
		xml.popTag();
	}
}

//---------------------------------
void lightMesh::saveConfig()
{
	ofxXmlSettings xml;
	auto pList = _mesh.getVertices();
	for (int i = 0; i < pList.size(); i++)
	{
		
		xml.addTag("vertex");
		xml.pushTag("vertex", i);
		xml.addValue("X", pList[i].x);
		xml.addValue("Y", pList[i].y);
		xml.popTag();
	}

	xml.saveFile("_config.xml");
}

//---------------------------------
vector<ofVec2f> lightMesh::getPath(int sIdx, int eIdx)
{
	int sy = int(sIdx / _colNum);
	int sx = int(sIdx % _colNum);
	int ey = int(eIdx / _colNum);
	int ex = int(eIdx % _colNum);

	int deltaX = ex - sx;
	int deltaY = ey - sy;

	vector<int> moveList;
	for (int i = 0; i < abs(deltaX); i++)
	{
		if (deltaX > 0)
		{
			moveList.push_back(1);
		}
		else
		{
			moveList.push_back(-1);
		}
	}

	for (int i = 0; i < abs(deltaY); i++)
	{
		if (deltaY > 0)
		{
			moveList.push_back(_colNum);
		}
		else
		{
			moveList.push_back(-_colNum);
		}
	}
	random_shuffle(moveList.begin(), moveList.end());

	vector<ofVec2f> path;
	int index = sIdx;
	for (auto& iter : moveList)
	{
		index += iter;
		path.push_back(_mesh.getVertex(index));
	}
	return path;
}

//---------------------------------
void lightMesh::editMode()
{
	_editMode ^= true;
	if (_editMode)
	{
		ofRegisterKeyEvents(this);
		_editIdx = 0;
	}
	else
	{
		ofUnregisterKeyEvents(this);
	}
}

void lightMesh::keyPressed(ofKeyEventArgs & e)
{
	if (!_editMode) {
		return;
	}

	switch (e.key)
	{
	case OF_KEY_LEFT:
	{
		updateVector(-1, 0);
		break;
	}
	case OF_KEY_RIGHT:
	{
		updateVector(1, 0);
		break;
	}
	case OF_KEY_UP:
	{
		updateVector(0, -1);
		break;
	}
	case OF_KEY_DOWN:
	{
		updateVector(0, 1);
		break;
	}
	case 'z':
	{
		_editIdx--;
		if (_editIdx <= 0)
		{
			_editIdx = _mesh.getNumVertices() - 1;
		}
		break;
	}
	case 'x':
	{
		_editIdx++;
		if (_editIdx >= _mesh.getNumVertices())
		{
			_editIdx = 0;
		}
		break;
	}
	case 'c':
	{
		saveConfig();
		break;
	}
	}
}
