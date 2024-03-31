#pragma once
#include <d3dx9.h>
#include "Keyboard.h"
#include "Object.h"
#include "GameDefine.h"
using namespace Define;

class Player;
class PlayerController
{
private:
	typedef void(PlayerController::* PlayerControllerF)(void);
	typedef map<int, PlayerControllerF> FunctionMap;
	FunctionMap _functionMap;

public:
	//Attack
	bool isAttack, isAllowAttack;

	Player* player;
	Keyboard* key;
public:
	PlayerController();
	~PlayerController();

	void StandState();
	void RunState();
	void MoveX();
	void Fall();
	void JumpState();
	void DeadState();
	void SitState();
	void SwimState();
	void DivingState();
	void PlayControllerF();
	void Update(float gameTime, Keyboard* key);
};