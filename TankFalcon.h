#pragma once
#include "OItem.h"

class TankFalcon : public OItem
{
public:

	TankFalcon() : OItem() {};
	~TankFalcon();

	void Init(D3DXVECTOR2 pos, int type = ItemType::M, int kind = 0);
	void Update(float gameTime, Keyboard* key);
};

