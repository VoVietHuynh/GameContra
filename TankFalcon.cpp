#include "TankFalcon.h"
#include "Player.h"

void TankFalcon::Init(D3DXVECTOR2 pos, int _type, int kind)
{
	AllowDraw = true;
	_itemType = (ItemType)_type;
	_kind = 1;
	position = pos;
	velocity = D3DXVECTOR2(0, 0);
	SetState(Object::Standing);
	this->SetBound(15, 32);
	HP = 1;
	type = _type;
	immortalTime = 0;
}

void TankFalcon::Update(float gameTime, Keyboard* key)
{
	if (State == Standing || State == Running)
	{
		immortalTime += gameTime;
		if (immortalTime > 1.5)//mo
		{
			State = Standing;
			isImmortal = false;
		}
		if (immortalTime > 2.5)//Dong
		{
			State = Standing;
			isImmortal = true;
		}
		if (immortalTime > 3)//
		{
			State = Running;
			isImmortal = false;
			immortalTime = 0;
		}
	}

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
	Object::Update(gameTime, key);

	Object::Log(State);
}