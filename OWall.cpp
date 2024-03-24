#include "OWall.h"
#include "Player.h"

OWall::OWall()
{
}

OWall::~OWall()
{
	delete _anim;
}

void OWall::Init(D3DXVECTOR2 pos, int _type, int kind)
{
	AllowDraw = false;
	Tag = Object::Wall;
	velocity = D3DXVECTOR2(0, 0);
	SetState(Object::Standing);
	HP = 999;

	position = pos;
	this->_walltype = (OWall::Walltype)_type;
	_kind = kind;
	this->type = _type;
}

void OWall::Controller()
{
}

D3DXVECTOR2 OWall::OnCollision(Object* obj, D3DXVECTOR2 side)
{
	return side;
}

void OWall::BeforeUpdate(float gameTime, Keyboard* key)
{
	this->Controller();
}

void OWall::Update(float gameTime, Keyboard* key)
{
	UpdateAnimation(gameTime);
	Object::Update(gameTime, key);
}

void OWall::UpdateAnimation(float gameTime)
{
}

void OWall::SetBound(float width, float height)
{
	InfoSprite::Infoframe info = _anim->GetCurrentFrameInfo();
	Width = info.w;
	Height = info.h;
	bound.left = position.x - Width / 2;
	bound.right = bound.left + Width;
	bound.top = position.y + Height / 2;
	bound.bottom = bound.top - Height;
}

void OWall::Render(Viewport* viewport)
{
}