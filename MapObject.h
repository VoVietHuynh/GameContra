#pragma once
#include<string>
#include "TinyXML\tinyxml.h"
using namespace std;

class MapObject
{
public:
	string name;
	float x, y, width, height;
	int id, kind = 0;
	MapObject(TiXmlElement *node,string name);
	~MapObject();
	void ReadXML(TiXmlElement *node,string name);
};
