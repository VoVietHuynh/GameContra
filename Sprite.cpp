#include "Sprite.h"

Sprite::Sprite()
{
}

//Contructor
Sprite::Sprite(string pathpng)
{
	SpriteGraphic = Graphic::GetInstance();
	Texture = SpriteGraphic->LoadTexture(pathpng, D3DCOLOR_XRGB(156, 252, 240));
	this->scale = D3DXVECTOR2(1, 1);
	transform = D3DXVECTOR2(0, 0);
	position = D3DXVECTOR2(0, 0);
	angle = 0;
	FlipFlag = false;
}

Sprite::~Sprite()
{
}

//Load lại Texture
void Sprite::SetTexture(string pathpng)
{
	Texture = SpriteGraphic->LoadTexture(pathpng, D3DCOLOR_XRGB(156, 252, 240));
}

//Get set các giá trị
//Chiều dài rộng frame;
float Sprite::GetWidthFrame()
{
	return rect.right - rect.left;
}
float Sprite::GetHeightFrame()
{
	return rect.bottom - rect.top;
}

//Rect
RECT Sprite::GetRect()
{
	return this->rect;
}
void Sprite::SetRect(RECT Rect)
{
	rect = Rect;
}

//Vị trí
D3DXVECTOR2 Sprite::GetPosition()
{
	return position;
}
void Sprite::SetPosition(D3DXVECTOR2 Position)
{
	position = Position;
}

//Vị trí vẽ
D3DXVECTOR2 Sprite::GetCenter()
{
	return center;
}
void Sprite::SetCenter(D3DXVECTOR2 Center)
{
	center = Center;
}

//Phóng ảnh
D3DXVECTOR2 Sprite::GetScale()
{
	return scale;
}
void Sprite::SetScale(D3DXVECTOR2 Scale)
{
	scale = Scale;
}

//Dịch chuyển
D3DXVECTOR2 Sprite::GetTransform()
{
	return transform;
}
void Sprite::SetTransform(float x, float y)
{
	transform.x = x;
	transform.y = y;
}

//Góc quay
float Sprite::GetAngle()
{
	return angle;
}
void Sprite::SetAngle(float Angle)
{
	angle = Angle;
}


void Sprite::SetFlipFlag(bool flag)
{
	FlipFlag = flag;
}

//Lật hình theo trục y
void Sprite::Flip(bool flag)
{
	if (flag)
	{
		scale = D3DXVECTOR2(-1, 1);
	}
	else scale = D3DXVECTOR2(1, 1);
}

//Set giá trị chuẩn bị vẽ
void Sprite::SetData(RECT Rect, D3DXVECTOR2 Center, D3DXVECTOR2 Position, D3DXVECTOR2 Scale, D3DXVECTOR2 Transform, float Angle)
{
	this->rect = Rect;
	this->center = Center;
	this->position = Position;
	this->scale = Scale;
	this->angle = Angle;
	this->transform = Transform;
}
//Vẽ sprite
void Sprite::Update(float gameTime)
{
}

//Vẽ Sprite lên màn hình
void Sprite::Render(Viewport* viewport)
{
	SpriteGraphic->DrawTexture(Texture, rect, center, viewport->GetPositionViewport(position), scale, transform, angle, D3DCOLOR_XRGB(225, 225, 225));
}

//Vẽ Sprite lên màn hình
void Sprite::Render()
{
	SpriteGraphic->DrawTexture(Texture, rect, center, position, scale, transform, angle, D3DCOLOR_XRGB(225, 225, 225));
}
