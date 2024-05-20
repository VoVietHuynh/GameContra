#include "bridge.h"
#include "Player.h"
#include "ObjectManager.h"

Animation* Bridge::GetAnimationEnemy()
{
	Animation::DataAnimMap data;
	// Soldier
	data[OWall::Brigde+ Object::Standing] = { 92 , 92 };
	data[OWall::Brigde + Object::Standing + 1] = { 93 , 93 };
	data[OWall::Brigde + Object::Standing + 2] = { 94 , 94 };

	Animation* _anim = new Animation(EnemyXML, EnemyPNG);
	_anim->SetDataAnimation(data);
	return _anim;
}


Bridge::Bridge()
{
	Tag = Object::Wall;
	_anim = GetAnimationEnemy();
}

void Bridge::Init(D3DXVECTOR2 pos, int _type, int kind)
{
	OWall::Init(pos, _type, kind);
	_kind = 0;
	AllowDraw = true;
	isExplode = false;
	explode = new Cannon();
}

void Bridge::Update(float gameTime, Keyboard* key)
{
	::Player* player = Player::GetInstance();
	if (player->position.x + 16 > bound.left)
	{
		isExplode = true;
	}
	explode->AllowDraw = false;
	if (isExplode && bound.left < bound.right)
	{
		timeExplode += gameTime;
		if (timeExplode > 0.5)
		{
			bound.left += 32;
			timeExplode = 0;

			explode->Init(D3DXVECTOR2(bound.left - 16, position.y - 16), OEnemy::Cannon, 0);
			explode->State = Dying;
		}
		explode->SetVelocity(0, 0);
		explode->Update(gameTime, key);
		explode->AllowDraw = true;
	}

	OWall::Update(gameTime, key);
	UpdateAnimation(gameTime);
}

void Bridge::Render(Viewport* viewport)
{

	D3DXVECTOR2 pos = position; pos.x -= 48;
	pos.y -= 8;
	if (pos.x > bound.left)
	{
		_anim->NewAnimationByIndex(_walltype + this->State);
		_anim->Update(0);
		_anim->SetPosition(pos);
		_anim->Render(viewport);
	}

	pos.x += 32;
	if (pos.x > bound.left)
	{
		_anim->NewAnimationByIndex(_walltype + this->State + 1);
		_anim->Update(0);
		_anim->SetPosition(pos);
		_anim->Render(viewport);
	}

	pos.x += 32;
	if (pos.x > bound.left)
	{
		_anim->NewAnimationByIndex(_walltype + this->State + 1);
		_anim->Update(0);
		_anim->SetPosition(pos);
		_anim->Render(viewport);
	}

	pos.x += 32;
	if (pos.x > bound.left)
	{
		_anim->NewAnimationByIndex(_walltype + this->State + 2);
		_anim->Update(0);
		_anim->SetPosition(pos);
		_anim->Render(viewport);
	}
	explode->Render(viewport);
}


void Bridge::UpdateAnimation(float gameTime)
{
	_anim->NewAnimationByIndex(_walltype + this->State);
	_anim->SetPosition(position);
	_anim->Update(gameTime);
}

Bridge::~Bridge()
{
}