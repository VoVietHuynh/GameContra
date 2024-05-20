#include "Tank.h"

void Tank::Init(D3DXVECTOR2 pos, int type, int kind)
{
	RifleMan::Init(pos, type, kind);
	this->SetBound(32, 32);
	maxBullet = 1;
	HP = 10;
}

void Tank::Controller()
{
	RifleMan::Controller();
	SetVelocity(0, 0);
}