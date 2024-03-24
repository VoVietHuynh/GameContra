#include "TileSet.h"

TileSet::TileSet()
{
}
TileSet::TileSet(int tilecount, int tilecolunm, float widthtile, float heighttile)
{
	TileCount = tilecount;

	WidthTile = widthtile;
	HeightTile = heighttile;
	TileColunms = tilecolunm;

	sprite = new Sprite(TileSetPNG);
	for (int i = 0; i < TileCount; i++)
	{	
		rect_tile[i].left = ((i % TileColunms)*WidthTile);
		rect_tile[i].top = (i / TileColunms)*HeightTile;
		rect_tile[i].right = rect_tile[i].left + WidthTile;
		rect_tile[i].bottom = rect_tile[i].top + HeightTile;
	}
}


TileSet::~TileSet()
{
	delete sprite;
}

//Get Id
int TileSet::GetId()
{
	return this->Id;
}

//Vẽ tile 
void TileSet::Render(Viewport* view, int id, D3DXVECTOR2 position)
{
	sprite->SetRect(rect_tile[id - 1]);
	sprite->SetPosition(position);
	sprite->Render(view);
}
