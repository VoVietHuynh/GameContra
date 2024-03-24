#pragma once
#include <d3dx9.h>
#include "TinyXML\tinyxml.h"
#include"MapObjectGroup.h"
#include<string>
#include<vector>
#include<map>
using namespace std;
class InfoMap
{
public:
	int width, height, tileCount, tileColumns;
	float tileWidth, tileHeight;
	map<int, map<int, int>> data;

	int numObjectGroups;
	vector<MapObjectGroup*> ObjectGroups;

public:
	InfoMap(const char *path);
	~InfoMap();
	void ReadXMl(const char *path);

	int GetData(int w, int h);
	void SetData(int w, int h, int Data);
};
