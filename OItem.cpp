#include "OItem.h"
#include "Player.h"
#include "FuncItem.h"
#include "Obullet.h"

Animation* OItem::GetAnimation()
{
	//Tạo Animation
	Animation::DataAnimMap data;
	// R
	data[OItem::R + Object::Standing + 1] = { 23 , 23};
	data[OItem::R + Object::Standing + 2] = { 24 , 26};
	data[OItem::R + Object::Running] = { 0 , 0 };
	data[OItem::R + Object::Running + 1] = { 27 , 29 };

	data[OItem::R + Object::Jumping] = { 5 , 5 };
	data[OItem::M + Object::Jumping] = { 4 , 4 };
	data[OItem::S + Object::Jumping] = { 6 , 6 };
	data[OItem::F + Object::Jumping] = { 2 , 2 };
	data[OItem::L + Object::Jumping] = { 3 , 3 };


	Animation* _animItem = new Animation(ItemXML, ItemPNG);
	_animItem->SetDataAnimation(data);
	return _animItem;
}

OItem::OItem()
{
	Tag = Object::Item;
	_anim = GetAnimation();
}

OItem::~OItem()
{
	delete _anim;
}

void OItem::Init(D3DXVECTOR2 pos, int _type, int kind)
{
	AllowDraw = true;
	_itemType = (ItemType)_type;
	_kind = 0;
	position = pos;
	velocity = D3DXVECTOR2(EnemySpeed/2, 0);
	SetState(Object::Running);
	this->SetBound(15, 32);
	HP = 1;
	type = _type;
	isImmortal = false;
}

void OItem::Controller()
{
	if (State == Object::Standing)
	{
		velocity = D3DXVECTOR2(0, 0);
		return;
	}
	if (State == Object::Jumping)
	{
		JumpState();
		return;
	}
	//velocity.y = Gravity;
}

D3DXVECTOR2 OItem::OnCollision(Object* obj, D3DXVECTOR2 side)
{
	switch (obj->Tag)
	{
	case Object::Wall:
		side.x = Collision::NONE;
		if (side.y == Collision::BOTTOM && State == Object::Jumping)
		{
			velocity = D3DXVECTOR2(0, 0);
			return side;
		}
		side.y = Collision::NONE;
		return side;
	default:
		return D3DXVECTOR2(Collision::NONE, Collision::NONE);
	}
}

void OItem::OnCollision(Object* obj)
{
	switch (obj->Tag)
	{
	case Object::Bullet:
		if (type != OBullet::EnemyBullet)
		{
			if (State == Running)
			{
				HP = 0;
			}
			obj->State = Dying;
		}
		break;
	case Object::Player:
		if (State == Jumping)
		{
			FuncItem::CallFunc(_itemType);
			State = Object::Dying;
		}
		return;
	default:
		return;
	}
}

void OItem::BeforeUpdate(float gameTime, Keyboard* key)
{
	this->SetBound(10, 15);
	this->Controller();
}

void OItem::Update(float gameTime, Keyboard* key)
{
	if (HP <= 0 && State == Object::Running)
	{
		velocity.x = (Player::GetInstance()->GetFlipFlag() ? -1 : 1) * EnemySpeed;
		StartJump(-Gravity / 1.5, 16, Gravity);
	}
	//Update Animation
	if (State == Object::Dying)
	{
		this->SetBound(0, 0);
		this->AllowDraw = false;
	}

	UpdateAnimation(gameTime);
	if (State == Object::Running)
	{
		position.x += velocity.x * gameTime;
		position.y += 5*sin(position.x/12);
		return;
	}
	Object::Update(gameTime, key);
}

void OItem::UpdateAnimation(float gameTime)
{
	if (State == Jumping)
		_anim->NewAnimationByIndex(_itemType + this->State);
	else
		_anim->NewAnimationByIndex(OItem::R + this->State + _kind + isImmortal);

	_anim->SetPosition(D3DXVECTOR2(position.x, position.y + Height / 2));
	//_anim->SetFlipFlag(velocity.x > 0);
	_anim->Update(gameTime);
}

void OItem::SetBound(float width, float height)
{
	InfoSprite::Infoframe info = _anim->GetCurrentFrameInfo();
	Width = info.w;
	Height = info.h;

	float w = width >= 0 ? width : Width;
	float h = height >= 0 ? height : Height;
	bound.left = position.x - w / 2;
	bound.right = bound.left + w;
	bound.top = position.y + h;
	bound.bottom = position.y;
}

void OItem::Render(Viewport* viewport)
{
	//Vẽ
	if (AllowDraw)
	{
		_anim->Render(viewport);
	}
}