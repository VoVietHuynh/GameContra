#include "Cannon.h"
#include "Player.h"

void Cannon::Init(D3DXVECTOR2 pos, int type, int kind)
{
	RifleMan::Init(pos, type, kind);
	State = Object::Running;
	this->SetBound(32, 32);
	maxBullet = 3;
	HP = 10;
	reload = 0.3;
}

void Cannon::Controller()
{
	if (State == Running)
	{
		isFlip = true;
		if (_anim->Index == _anim->GetEnd())
		{
			State = Standing;
		}
		SetVelocity(0, 0);
		return;
	}
	RifleMan::Controller();
	SetVelocity(0, 0);
}

void Cannon::AttackState()
{
	D3DXVECTOR2 posPlayer = Player::GetInstance()->GetPosition();
	isFlip = posPlayer.x < position.x;

	AngleGun = 0;
	int range = 10;
	if (posPlayer.y > position.y + range)
	{
		if (abs(posPlayer.x - position.x) > range/2)
		{
			AngleGun = 45;
		}
		else AngleGun = 90;
	}
}