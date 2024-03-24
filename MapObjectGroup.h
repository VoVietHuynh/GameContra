#pragma once
#include<string>
#include "TinyXML\tinyxml.h"
#include <vector>
#include"MapObject.h"

using namespace std;

class MapObjectGroup
{
public:
	string name;
	vector<MapObject*> Objects;
	int NumOnjects;
	MapObjectGroup(TiXmlElement *node);
	~MapObjectGroup();
	void ReadXML(TiXmlElement *node);
};