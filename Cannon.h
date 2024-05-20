#pragma once
#include "RifleMan.h"
class Cannon : public RifleMan
{
public:
	Cannon() : RifleMan() {};
	~Cannon();

	void Init(D3DXVECTOR2 pos, int type = Enemytype::Cannon, int kind = 0);
	void Controller();
	void AttackState();
};

