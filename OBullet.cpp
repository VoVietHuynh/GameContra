#include "OBullet.h"
#include "Player.h"
#include "ObjectManager.h"

Animation* OBullet::GetAnimationBullet()
{
	//Tạo Animation
	Animation::DataAnimMap data;
	// Soldier
	data[OBullet::NormalBullet + Object::Running] = { 14 , 14 };
	data[OBullet::NormalBullet + Object::Dying] = { 15 , 16 };


	Animation* _animEnemy = new Animation(ItemXML, ItemPNG);
	_animEnemy->SetDataAnimation(data);
	return _animEnemy;
}

OBullet::OBullet()
{
}

OBullet::~OBullet()
{
	delete _anim;
}

void OBullet::Init(int acceleration, D3DXVECTOR2 pos, int _type, int kind)
{
	AllowDraw = true;
	Tag = Object::Bullet;

	_anim = GetAnimationBullet();
	_bulletType = (Bullettype)_type;
	_kind = kind;
	position = pos;
	velocity = D3DXVECTOR2(BulletSpeed * acceleration, 0);
	SetState(Object::Running);
	SetPositionStart(pos);
	this->SetBound(8, 8);
	HP = 1;
	Damage = 1;
	type = _type;

	ObjectManager::GetInstance()->AddObjectMap(this);
}

void OBullet::Controller()
{
	velocity.y = 0;
}

D3DXVECTOR2 OBullet::OnCollision(Object* obj, D3DXVECTOR2 side)
{
	switch (obj->Tag)
	{
	case Object::Enemy:
		OnCollision(obj);
		return side;
	default:
		return D3DXVECTOR2(Collision::NONE, Collision::NONE);
	}
}

void OBullet::OnCollision(Object* obj)
{
	switch (obj->Tag)
	{
	case Object::Enemy:
		velocity.x = 0;
		this->State = Object::Dying;
		obj->SetHP(obj->GetHP() - this->Damage);
		break;
	default:
		break;
	}
}

void OBullet::BeforeUpdate(float gameTime, Keyboard* key)
{
	this->SetBound(8, 8);
	this->Controller();
}

void OBullet::Update(float gameTime, Keyboard* key)
{
	//Update Animation
	if (State == Object::Dying)
	{
		this->SetBound(0, 0);
		this->SetVelocity(0, 0);
		timeDead += gameTime;
		if (timeDead > 0.2)
			AllowDraw = false;
	}

	UpdateAnimation(gameTime);

	Object::Update(gameTime, key);
}

void OBullet::UpdateAnimation(float gameTime)
{
	_anim->NewAnimationByIndex(_bulletType + this->State + _kind);
	_anim->SetPosition(position);
	//_anim->SetFlipFlag(velocity.x > 0);
	_anim->Update(gameTime);
}

void OBullet::SetBound(float width, float height)
{
	InfoSprite::Infoframe info = _anim->GetCurrentFrameInfo();
	Width = info.w;
	Height = info.h;

	float w = width >= 0 ? width : Width;
	float h = height >= 0 ? height : Height;
	bound.left = position.x - w / 2;
	bound.right = bound.left + w;
	bound.top = position.y + h/2;
	bound.bottom = bound.top - h;
}

void OBullet::Render(Viewport* viewport)
{
	//Vẽ OBullet
	if (AllowDraw)
	{
		_anim->Render(viewport);
	}
}