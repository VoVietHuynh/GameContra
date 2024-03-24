#include "PlayerController.h"
#include "Player.h"

PlayerController::PlayerController()
{
	player = Player::GetInstance();
	player->SetState(Object::Standing);
	isAllowJump = false;
	isFall = true;
	isAttack = false;

	_functionMap[Object::Standing] = &PlayerController::StandState;
	_functionMap[Object::Running] = &PlayerController::RunState;
	_functionMap[Object::Jumping] = &PlayerController::JumpState;
	_functionMap[Object::Dying] = &PlayerController::DeadState;
	_functionMap[Object::Sitting] = &PlayerController::SitState;

}

PlayerController::~PlayerController()
{
}

//Trạng thái Đứng
void PlayerController::StandState() //reset all state
{
}

//Trang thái chạy
void PlayerController::RunState()
{
}

void PlayerController::MoveX()
{
	//Nếu chết rồi không có di chuyển
	if (player->State == Object::Dying)
	{
		player->SetVelocityX(0);
		return;
	}

	float speed = 0;
	player->State = Object::Standing;
	player->SetVelocityY(Gravity);

	if (key->IsKeyDown(Dik_RIGHT) && player->State != Object::Sitting)
	{
		player->State = Object::Running;
		player->SetFlipFlag(false);
		speed = RunSpeed;
	}
	else if (key->IsKeyDown(Dik_LEFT) && player->State != Object::Sitting)
	{
		player->State = Object::Running;
		player->SetFlipFlag(true);
		speed = -RunSpeed;
	}
	player->SetVelocityX(speed);
}

void PlayerController::Fall()
{
}

//Trạng thái nhảy
void PlayerController::JumpState()
{
}

//Trạng thái chêt
void PlayerController::DeadState()
{
}

//Trạng thái ngồi
void PlayerController::SitState()
{
}

void PlayerController::PlayControllerF()
{
	//Lấy Function từ player state
	FunctionMap::iterator it = _functionMap.find(player->State);
	(this->*(it->second))();
}

void PlayerController::Update(float gameTime, Keyboard* key)
{
	this->key = key;
	MoveX();
	this->PlayControllerF();

	if (key->GIsKeyUp(Dik_ATTACK))
		//Tạo Đạn Theo Súng
		isAllowAttack = true;
}