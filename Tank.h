#pragma once
#include "RifleMan.h"
class Tank : public RifleMan
{
public:
	Tank() : RifleMan() {};
	~Tank();

	void Init(D3DXVECTOR2 pos, int type = Enemytype::Tank, int kind = 0);
	void Controller();
};

