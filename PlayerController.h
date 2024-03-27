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
	//Run
	bool isBake, isCount, isSpeed;
	float accDown;
	int accCount = 0;
	//Jump
	bool isAllowJump, isFall, isFallDown, isSpeedJump, isShortJump, isFly;
	float posYStartJump, velYStartFall, maxJump, fallAc, timeFlyDown;
	//Attack
	bool isAttack, isAllowAttack;
	float timeAc;


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