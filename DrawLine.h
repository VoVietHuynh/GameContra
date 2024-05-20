#pragma once
#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include "Graphic.h"
#include "Viewport.h"

class DrawLine
{

private:
	static DrawLine* _drawLine;
	D3DCOLOR _color;
public:
	DrawLine();
	~DrawLine();
	static DrawLine* GetInstance();

	void Draw(D3DXVECTOR2 lines[], int count);
	void DrawRect(RECT rect);
	void SetColor(D3DCOLOR Color);
	void SetColor(int r, int g, int b);
};

