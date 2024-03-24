#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include"Graphic.h"
class DrawString
{
protected:
	Graphic *graphic;
	ID3DXFont *mFont;
public:
	DrawString(Graphic *g,int size);
	~DrawString();
	void Render(char * text, RECT r, D3DCOLOR color);
};