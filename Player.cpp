#include "Player.h"
#include "GameDefine.h"
#include <math.h>
#include "GUI.h"
#include "ObjectManager.h"
#include "Obullet.h"
#pragma warning(disable : 4996)

Player* Player::_player = nullptr;
Player::Player()
{
}

Player* Player::GetInstance()
{
	if (nullptr == _player) {
		_player = new Player();
		_player->_life = StartLive;
		_player->Init();
	}
	return _player;
}

Player::~Player()
{
	delete _playerController;
	delete _playerCollision;
	delete _player;
}

Animation::DataAnimMap dataM()
{
	//Tạo Animation
	Animation::DataAnimMap data;
	//Small
	data[Player::Blue + Object::Standing] = { 0, 0 };
	data[Player::Blue + Object::Standing + 1] = { 48, 48 };
	data[Player::Blue + Object::Running] = { 1, 6 };
	data[Player::Blue + Object::Jumping] = { 7, 10 };
	data[Player::Blue + Object::Sitting] = { 11, 11 };
	data[Player::Blue + Object::Sitting + 1] = { 12, 12 };
	data[Player::Blue + Object::Dying] = { 44, 47 };
	data[Player::Blue + Object::Diving] = { 36, 37 };
	data[Player::Blue + Object::Swimming] = { 34, 35, 150 };
	data[Player::Blue + Object::Swimming + 1] = { 38, 39, 150 };


	return data;
}

void Player::Init()
{
	//Tạo class xử lý va chạm
	_playerController = new PlayerController();
	_playerCollision = new PlayerCollision();

	AllowDraw = true;
	Tag = Object::Player;
	_playerType = Player::Blue;
	position = positionStart;
	velocity = D3DXVECTOR2(0, 0);
	SetState(Object::Standing);
	HP = 1;
	type = _playerType;

	Animation::DataAnimMap data = dataM();
	_anim = new Animation(PlayerXML, PlayerPNG);
	_anim->SetDataAnimation(data);
	SetBound(40, 40);
}

void Player::BeforeUpdate(float gameTime, Keyboard* key)
{
	_playerCollision->isGround = false;

	this->SetBound(Width, Height);
	//Check handler controller
	_playerController->Update(gameTime, key);
}

void Player::OnCollision(Object* obj, float gameTime)
{
	Object::OnCollision(obj, gameTime);
	if (obj->State == Object::Dying || this->State == Object::Dying)
		return;
}

D3DXVECTOR2 Player::OnCollision(Object* obj, D3DXVECTOR2 side)
{
	_playerCollision->_obj = obj;
	_playerCollision->_side = side;
	_playerCollision->OnCollision();
	return _playerCollision->_side;
}

void Player::OnCollision(Object* obj)
{
	
}

void Player::Update(float gameTime, Keyboard* key)
{
	if (!_playerCollision->isGround) State = Object::Jumping;

	//Update Animation
	UpdateAnimation(gameTime);

	Object::Update(gameTime, key);

	for (size_t i = 0; i < ListBullet.size(); i++)
	{
		if (abs(positionStart.x - ListBullet.at(i)->GetPosition().x) > GameWidth/2 || ListBullet.at(i)->GetState() == Object::Dying)
		{
			ListBullet.erase(std::next(ListBullet.begin(), i));
		}
	}
}

void Player::UpdateAnimation(float gameTime)
{
	_anim->NewAnimationByIndex(_playerType + this->State + _playerController->isAttack);
	_anim->SetPosition(D3DXVECTOR2(position.x, position.y + Height / 2));
	_anim->SetFlipFlag(isFlip);
	_anim->Update(gameTime);
}

void Player::SetImmortal(float time)
{
	immortalTime = time;
	isImmortal = true;
}

void Player::SetBound(float width, float height)
{
	//InfoSprite::Infoframe info = _anim->GetCurrentFrameInfo();
	Width = width;
	Height = height;
	bound.left = position.x - Width / 2;
	bound.right = bound.left + Width;
	bound.top = position.y + Height;
	bound.bottom = position.y;
}

void Player::Render(Viewport* viewport)
{
	//Vẽ Player
	if (AllowDraw)
	{
		_anim->Render(viewport);
	}

	GUI::GetInstance()->Render("State: ", { 150, 200, 200, 235 });
	GUI::GetInstance()->Render(State, { 210, 200, 230, 235 });
}
