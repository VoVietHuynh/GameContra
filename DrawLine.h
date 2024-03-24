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
public:
	DrawLine();
	~DrawLine();
	static DrawLine* GetInstance();

	void Draw(D3DXVECTOR2 lines[], int count);
	void DrawRect(RECT rect);
};

