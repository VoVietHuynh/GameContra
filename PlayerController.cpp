#include "PlayerController.h"
#include "Player.h"

PlayerController::PlayerController()
{
	player = Player::GetInstance();
	player->SetState(Object::Standing);
	isAttack = false;

	_functionMap[Object::Standing] = &PlayerController::StandState;
	_functionMap[Object::Running] = &PlayerController::StandState;
	_functionMap[Object::Jumping] = &PlayerController::JumpState;
	_functionMap[Object::Dying] = &PlayerController::DeadState;
	_functionMap[Object::Sitting] = &PlayerController::SitState;
	_functionMap[Object::Swimming] = &PlayerController::SwimState;
	_functionMap[Object::Diving] = &PlayerController::DivingState;
}

PlayerController::~PlayerController()
{
}

//Trạng thái Đứng
void PlayerController::StandState() //reset all state
{
	player->State = player->GetVelocity().x != 0 ? Object::Running : Object::Standing;
	player->SetBound(20, 35);

	if (key->IsKeyDown(Dik_JUMP))
	{
		JumpState();
		player->SetVelocityY(-Gravity);
		return;
	}

	if (key->IsKeyDown(Dik_DOWN))
	{
		SitState();
		return;
	}
}

//Trang thái chạy
void PlayerController::RunState()
{
}

void PlayerController::Fall()
{
}

//Trạng thái nhảy
void PlayerController::JumpState()
{
	player->State = Object::Jumping;
	player->SetBound(20, 20);
	player->SetVelocityY(player->GetVelocity().y + Gravity/25);
}

//Trạng thái chêt
void PlayerController::DeadState()
{
	player->State = Object::Dying;

}

//Trạng thái ngồi
void PlayerController::SitState()
{
	player->isFall = false;
	player->State = Object::Sitting;
	player->SetBound(32, 16);
	if (key->GIsKeyUp(Dik_DOWN))
	{
		StandState();
		return;
	}

	if (key->IsKeyDown(Dik_JUMP))
	{
		player->isFall = true;
		return;
	}
}

void PlayerController::SwimState()
{
	player->State = Object::Swimming;
	player->SetBound(25, 16);
	if (key->IsKeyDown(Dik_JUMP))
	{
		JumpState();
		player->SetVelocityY(-Gravity);
		return;
	}

	if (key->IsKeyDown(Dik_DOWN))
	{
		DivingState();
		return;
	}
}

void PlayerController::DivingState()
{
	player->State = Object::Diving;
	player->SetBound(25, 10);
	if (key->GIsKeyUp(Dik_DOWN))
	{
		SwimState();
		return;
	}
}

void PlayerController::MoveX()
{
	//Nếu chết rồi không có di chuyển
	if (player->State == Object::Dying || player->State == Object::Sitting || player->State == Object::Diving)
	{
		player->SetVelocityX(0);
		return;
	}

	float speed = 0;
	if (key->IsKeyDown(Dik_RIGHT))
	{
		player->SetFlipFlag(false);
		speed = RunSpeed;
	}
	else if (key->IsKeyDown(Dik_LEFT))
	{
		player->SetFlipFlag(true);
		speed = -RunSpeed;
	}
	player->SetVelocityX(speed);
}

void PlayerController::PlayControllerF()
{
	//Lấy Function từ player state
	
	FunctionMap::iterator it = _functionMap.find(player->State);
	if( it != _functionMap.end())
	(this->*(it->second))();
	
}

void PlayerController::Update(float gameTime, Keyboard* key)
{
	this->key = key;
	MoveX();
	if (player->State != Object::Jumping) {
		player->SetVelocityY(-1);
	}

	this->PlayControllerF();

	if (key->GIsKeyUp(Dik_ATTACK))
		//Tạo Đạn Theo Súng
		isAllowAttack = true;
}