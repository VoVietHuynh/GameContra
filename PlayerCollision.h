#pragma once
#include "Collision.h"
#include "Object.h"
#include "GameDefine.h"

using namespace Define;
class Player;
class PlayerCollision : public Collision
{
private:
	typedef void(PlayerCollision::* playerCollisionF)(void);
	typedef map<int, playerCollisionF> FunctionMap;
	FunctionMap _functionMap;
public:
	Player* player;
	Object* _obj;
	D3DXVECTOR2 _side;
	bool isGround, isCollisionTop;
public:
	PlayerCollision();
	~PlayerCollision();

	void CheckCollisionWall(Object* block = nullptr);
	void OnCollision();
	void PlayCollisionF();

	void StandCollision();
	void RunCollision();
};

