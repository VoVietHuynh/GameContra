#include "Viewport.h"



Viewport::Viewport()
{
}

Viewport::Viewport(float x, float y)
{
	this->position_of_world.x =x;
	this->position_of_world.y =y;
	//Mặc định là kích thước game
	this->Width = GameWidth;
	this->Height = GameHeight;
}

Viewport::Viewport(float x, float y, float width, float height)
{
	this->position_of_world.x = x;
	this->position_of_world.y = y;
	this->Width = width;
	this->Height = height;
}

Viewport::~Viewport()
{
}

//Get set vị trí Viewport
D3DXVECTOR2 Viewport::GetPosition()
{
	return position_of_world;
}
void Viewport::SetPosition(D3DXVECTOR2 Position)
{
	position_of_world = Position;
}
void Viewport::SetPositionX(float x)
{
	position_of_world.x = x;	
}
void Viewport::SetPositionY(float y)
{
	position_of_world.y = y;
}

//Lấy chiều dài rộng của Viewport
float Viewport::GetWidth()
{
	return this->Width;
}
float Viewport::GetHeight()
{
	return this->Height;
}

//Lấy vị trí của ViewPort từ vị trị object cần vẽ theo hệ trục left-top
D3DXVECTOR2 Viewport::GetPositionViewport_Left_Top(D3DXVECTOR2 Position)
{
	return Position-position_of_world;
}

//Lấy vị trí của ViewPort từ vị trị object cần vẽ theo hệ đề các
D3DXVECTOR2 Viewport::GetPositionViewport(D3DXVECTOR2 Position)
{
	D3DXVECTOR3* position = &D3DXVECTOR3(Position.x, Position.y, 0);

	D3DXMATRIX mt;
	D3DXVECTOR4 posViewport;

	//đổi ma trận chuẩn bị nhân lấy tọa độ mới
	D3DXMatrixIdentity(&mt);
	mt._22 = -1.0f;
	mt._41 = -(int)position_of_world.x;
	mt._42 = (int)position_of_world.y;

	D3DXVec3Transform(&posViewport, position, &mt);

	return D3DXVECTOR2((int)posViewport.x, (int)posViewport.y);
}

//Kiểm tra 1 rect có ở trong màn hình không
bool Viewport::isContains(RECT rect)
{
	if (rect.right < position_of_world.x)
		return false;
	if (rect.bottom > position_of_world.y)
		return false;
	if (rect.left > position_of_world.x + Width)
		return false;
	if (rect.top < position_of_world.y - Height)
		return false;

	return true;
}

//Kích thước RECT màn hình tính trong World
RECT Viewport::GetBoundViewport()
{
	RECT rect;

	rect.left = position_of_world.x;
	rect.top = position_of_world.y;
	rect.bottom = rect.top - Height;
	rect.right = rect.left + Width;

	return rect;
}


//Kích thước RECT màn hình tính trong World
RECT Viewport::GetBoundViewport1()
{
	RECT rect;

	rect.left = position_of_world.x - 30;
	rect.top = position_of_world.y + 30;
	rect.bottom = rect.top - Height - 30;
	rect.right = rect.left + Width + 30;

	return rect;
}

//Update theo 1 đối tượng
void Viewport::Update(float gameTime, Keyboard* key, D3DXVECTOR2 &posobject)
{
	//posPlayer
	if (posobject.x - position_of_world.x <= 112)
		position_of_world.x = posobject.x - 112;
	else if (posobject.x - position_of_world.x >= 144)
		position_of_world.x = posobject.x - 144;

	if (position_of_world.y - posobject.y <= 112)
		position_of_world.y = posobject.y + 112;
	else if (position_of_world.y - posobject.y >= 144)
		position_of_world.y = posobject.y + 144;

	//rect
	RECT boundView = GetBoundViewport();
	if (boundView.left <= RectView.left)
		position_of_world.x = RectView.left;
	else if (boundView.right >= RectView.right)
		position_of_world.x = RectView.right - Width;

	if (boundView.top >= RectView.top)
		position_of_world.y = RectView.top;
	else if (boundView.bottom <= RectView.bottom)
		position_of_world.y = RectView.bottom + Height;

	
	if (position_of_world.x > RectView.left)
	{
		RectView.left = position_of_world.x;
	}
}