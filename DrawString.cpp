#include"DrawString.h"

DrawString::~DrawString() 
{
	if (mFont != NULL)
	{
		mFont->Release();
		mFont = NULL;
	}
}
DrawString::DrawString(Graphic *g, int size)
{
	this->graphic = g;
	D3DXCreateFont(g->GetDevice(),    // the D3D Device
		size,  // font height
		0,    // default font width
		FW_NORMAL,    // font weight
		1,    // not using MipLevels
		false,    // italic font
		DEFAULT_CHARSET,    // default character set
		OUT_DEFAULT_PRECIS,    // default OutputPrecision,
		DEFAULT_QUALITY,    // default Quality
		DEFAULT_PITCH | FF_DONTCARE,    // default pitch and family
		"Arial Black",    // use Facename Arial Black
		&mFont);
}

void DrawString::Render(char* text,RECT r, D3DCOLOR color)
{
	mFont->DrawTextA(this->graphic->GetSprite(),
		text,
		-1,
		&r,
		DT_RIGHT | DT_TOP,
		color);
}
