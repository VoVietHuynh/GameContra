#pragma once
#include "OEnemy.h"
class RifleMan : public OEnemy
{
public:
	RifleMan() : OEnemy() {};
	~RifleMan();

	void Init(D3DXVECTOR2 pos, int type = Enemytype::Rifleman, int kind = 0);
	void Controller();
	void AttackState();
};

