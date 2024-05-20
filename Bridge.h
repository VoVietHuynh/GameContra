#pragma once
#include "Water.h"

class Bridge : public OWall
{
public:
	bool isExplode;
	float timeExplode;
	Object* explode;
	Bridge();
	~Bridge();

	void Init(D3DXVECTOR2 pos, int type = Walltype::Brigde, int kind = 0);
	void Update(float gameTime, Keyboard* key);
	void Render(Viewport* viewport);
	void UpdateAnimation(float gameTime);
	static Animation* GetAnimationEnemy();
};

