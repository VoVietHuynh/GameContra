#pragma once
#include "Viewport.h"
#include "TileSet.h"
#include "GameDefine.h"
#include "InfoMap.h"
#include "Cannon.h"
#include "Tank.h"
#include "TankFalcon.h"
#include "BinaryTree.h"
#include "Bridge.h"


using namespace Define;

class Map
{
public:
	GSound* gSound;
	//tính theo tile
	int WidthMap, HeightMap;
	TileSet* tileset;
	D3DXVECTOR2 position;
	InfoMap *info;
	map<string, int> objectTag;
	vector <Object*> ListObject;

	BinaryTree* Tree;
public:
	Map();
	~Map();

	Object* CreateObject(MapObject* _mapobject);

	void Render(Viewport * view);
};

