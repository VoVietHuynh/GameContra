#pragma once
#include <d3dx9.h>
#include <vector>
#include "Keyboard.h"
#include "GameDefine.h"

using namespace Define;


class Viewport
{
protected:
	//Tọa độ Viewport là hệ tọa độ Đề các left-bot
	D3DXVECTOR2 positionWorld;
	float Width;
	float Height;

public:
	RECT _rect;
	float _left = 0;
	float _right = 0;
	bool isMoveTop = false;

public:
	Viewport();
	//x và y là tọa độ thế giới left-top
	Viewport(float x, float y);
	Viewport(float x, float y, float width, float height);

	~Viewport();

	D3DXVECTOR2 GetPosition();
	void SetPosition(D3DXVECTOR2 Position);
	void SetPositionX(float x);
	void SetPositionY(float y);
	float GetWidth();
	float GetHeight();

	D3DXVECTOR2 GetPositionViewport_Left_Top(D3DXVECTOR2 Position);
	D3DXVECTOR2 GetPositionViewport(D3DXVECTOR2 Position);
	//Kiểm tra 1 rect còn trong màn hình không
	bool isContains(RECT rect);
	//Kích thước RECT màn hình tính trong World
	RECT GetBoundViewport();

	//Update View theo 1 đối tượng
	void Update(float gameTime, Keyboard* key, D3DXVECTOR2 &posobject);
};

