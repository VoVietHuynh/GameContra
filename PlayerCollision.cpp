#include "PlayerCollision.h"
#include "Player.h"
#include "OWall.h"

PlayerCollision::PlayerCollision()
{
	player = Player::GetInstance();
	_functionMap[Object::Standing] = &PlayerCollision::StandCollision;
	_functionMap[Object::Running] = &PlayerCollision::RunCollision;
	_functionMap[Object::Jumping] = &PlayerCollision::JumpCollision;
	_functionMap[Object::Sitting] = &PlayerCollision::StandCollision;
}

PlayerCollision::~PlayerCollision()
{
}

void PlayerCollision::OnCollision()
{
	//Check player collision by state
	PlayCollisionF();

	//CheckAllState
	switch (_obj->Tag)
	{
	case Object::Wall:
		CheckCollisionWall();
		break;
	default:

		break;
	}

	//Kiểm tra player rơi
	isGround = isGround || _side.y == Collision::BOTTOM;
}


//Va chạm với Tường
void PlayerCollision::CheckCollisionWall(Object* _wall)
{
	if (_wall == nullptr) _wall = _obj;
	OWall* wall = dynamic_cast<OWall*>(_wall);
	switch (wall->_walltype)
	{
	case OWall::Wall:
		if (_side.y == Collision::BOTTOM && player->State == Object::Jumping)
		{
			player->State = Object::Standing;
		}
		//if (_side.y == Collision::BOTTOM && player->State == Object::Sitting)
		//{
		//	player->State = Object::Jumping;
		//	player->SetPositionY(player->GetPosition().y - 2);
		//}
		break;
	case OWall::Water:
		if (_side.y == Collision::BOTTOM && player->State == Object::Jumping)
		{
			player->State = Object::Swimming;
		}
		break;
	default:
		break;
	}
}

//Chạy function ứng với state player
void PlayerCollision::PlayCollisionF()
{
	//Lấy Function từ player state
	FunctionMap::iterator it = _functionMap.find(player->State);
	//(it->second) là con trỏ hàm lấy từ <map> = &StandCollision(
	if (it != _functionMap.end())
	(this->*(it->second))();	//	(this->*(it->second)) = this->StandCollision
}

//Va chạm khi đứng
void PlayerCollision::StandCollision()
{
}

//Va chạm khi đứng
void PlayerCollision::JumpCollision()
{
}


//Va chạm khi chạy
void PlayerCollision::RunCollision()
{
	if (_side.x != Collision::NONE)
	{
		player->State = Object::Standing;
	}
}