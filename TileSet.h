#pragma once
#include "Sprite.h"
#include "Viewport.h"
#include <vector>
#include "Graphic.h"
using namespace std;

class TileSet
{
protected:
	Sprite* sprite;
	RECT rect_tile[880];
	float WidthTile, HeightTile;
	int Id, TileColunms,TileCount;
public:
	TileSet();
	TileSet(int tilecount, int tilecolunm, float widthtile, float heighttile);
	~TileSet();

	int GetId();

	void Render(Viewport* view, int id, D3DXVECTOR2 position);
};

