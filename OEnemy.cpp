#include "OEnemy.h"
#include "Player.h"

Animation* OEnemy::GetAnimationEnemy()
{
	//Tạo Animation
	Animation::DataAnimMap data;
	// Soldier
	data[OEnemy::Soldier + Object::Standing] = { 0 , 5};
	data[OEnemy::Soldier + Object::Dying] = { 86 , 88 };


	data[OEnemy::Rifleman + Object::Standing] = { 11, 12 };
	data[OEnemy::Rifleman + Object::Standing + 2] = { 13, 14 };//Khong co ban chi co gio sung thoi
	data[OEnemy::Rifleman + Object::Standing + 4] = { 13, 14 };
	data[OEnemy::Rifleman + Object::Standing + 6] = { 15, 15 };
	data[OEnemy::Rifleman + Object::Standing + 8] = { 15, 15 };

	data[OEnemy::Rifleman + Object::Diving] = { 16, 16};
	data[OEnemy::Rifleman + Object::Jumping] = { 17, 18 };
	data[OEnemy::Rifleman + Object::Dying] = { 86, 88 };

	data[OEnemy::Tank + Object::Standing] = { 21, 23 };
	data[OEnemy::Tank + Object::Standing + 2] = { 36, 38 };
	data[OEnemy::Tank + Object::Standing + 4] = { 24, 26 };
	data[OEnemy::Tank + Object::Standing + 6] = { 30, 32 };
	data[OEnemy::Tank + Object::Standing + 8] = { 39, 41 };
	data[OEnemy::Tank + Object::Dying] = { 89, 91 };

	data[OEnemy::Cannon + Object::Running] = { 79, 86 };
	data[OEnemy::Cannon + Object::Standing] = { 85, 85 };
	data[OEnemy::Cannon + Object::Standing + 2] = { 85, 85 };
	data[OEnemy::Cannon + Object::Standing + 4] = { 53, 53 };
	data[OEnemy::Cannon + Object::Dying] = { 89, 91 };

	Animation* _animEnemy = new Animation(EnemyXML, EnemyPNG);
	_animEnemy->SetDataAnimation(data);
	return _animEnemy;
}

OEnemy::OEnemy()
{
	Tag = Object::Enemy;
	_anim = GetAnimationEnemy();
}

OEnemy::~OEnemy()
{
	delete _anim;
}

void OEnemy::Init(D3DXVECTOR2 pos, int _type, int kind)
{
	AllowDraw = true;

	_enemyType = (Enemytype)_type;
	_kind = kind;
	position = pos;
	velocity = D3DXVECTOR2(-EnemySpeed, Gravity);
	SetState(Object::Standing);
	this->SetBound(15, 32);
	HP = 1;
	type = _type;
	GunType = 10000;
}

void OEnemy::Controller()
{
	isFlip = velocity.x < 0;
	if (State == Object::Jumping)
	{
		JumpState();
		return;
	}
	velocity.y = Gravity;
}

D3DXVECTOR2 OEnemy::OnCollision(Object* obj, D3DXVECTOR2 side)
{
	switch (obj->Tag)
	{
	case Object::Wall:
		if (side.x != Collision::NONE)
		{
			velocity.x = -velocity.x;
			side.x = Collision::NONE;
		}
		if (side.y == Collision::BOTTOM)
		{
			SetState(Object::Standing);
			if (position.x < obj->GetBound().left || position.x > obj->GetBound().right)
			{
				StartJump(-Gravity/2, 16, Gravity);
			}
		}
		return side;
	case Object::Bullet:
		obj->OnCollision(this);
		return D3DXVECTOR2(Collision::NONE, Collision::NONE);
	default:
		return D3DXVECTOR2(Collision::NONE, Collision::NONE);
	}
}

void OEnemy::OnCollision(Object* obj)
{
	switch (obj->Tag)
	{
	case Object::Player:
		if (obj->State != Dying)
		{
			Player::GetInstance()->SetHP(Damage);
		}
		return;
	default:
		return;
	}
}

void OEnemy::BeforeUpdate(float gameTime, Keyboard* key)
{
	if (State == Object::Dying)
	{
		SetVelocity(0, 0);
		this->SetBound(0, 0);
		return;
	}
	this->SetBound(15, 32);
	this->Controller();
}

void OEnemy::Update(float gameTime, Keyboard* key)
{
	if (HP <= 0 && State != Object::Dying)
	{
		if (gSound == NULL)
			gSound = Object::PlaySoundA("./Resource Files/Sound/Destroy_Enemy.wav");
		else
			Object::PlaySoundA(gSound);

		velocity.x = (Player::GetInstance()->GetFlipFlag()?-1:1)*EnemySpeed;
		StartJump(-Gravity / 2, 16, Gravity);
		State = Object::Dying;
	}
	//Update Animation
	if (State == Object::Dying)
	{
		this->SetBound(0, 0);
		JumpState();
		timeDead += gameTime;
		if (timeDead > 0.2)
			AllowDraw = false;
	}
	UpdateAnimation(gameTime);

	Object::Update(gameTime, key);
	timeAttack += gameTime;
}

void OEnemy::UpdateAnimation(float gameTime)
{
	_anim->NewAnimationByIndex(_enemyType + this->State + GetIndexGun());
	int h = _anim->GetCurrentFrameInfo().h;
	_anim->SetPosition(D3DXVECTOR2(position.x, position.y + h / 2));
	_anim->SetFlipFlag(!isFlip);
	_anim->Update(gameTime);
}

void OEnemy::SetBound(float width, float height)
{
	InfoSprite::Infoframe info = _anim->GetCurrentFrameInfo();
	Width = info.w;
	Height = info.h;

	float w = width >= 0 ? width : Width;
	float h = height >= 0 ? height : Height;
	bound.left = position.x - w / 2;
	bound.right = bound.left + w;
	bound.top = position.y + h;
	bound.bottom = position.y;
}

void OEnemy::Render(Viewport* viewport)
{
	//Vẽ OEnemy
	if (AllowDraw)
	{
		_anim->Render(viewport);
	}
}