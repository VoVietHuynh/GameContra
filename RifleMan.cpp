#include "RifleMan.h"
#include "FuncItem.h"
#include "OBullet.h"
#include "Player.h"

void RifleMan::Init(D3DXVECTOR2 pos, int type, int kind)
{
	OEnemy::Init(pos, type, kind);
	velocity = D3DXVECTOR2(0, Gravity);
	SetState(Object::Standing);
	this->SetBound(15, 32);
	reload = 0.3;
	maxBullet = 3;
}

void RifleMan::Controller()
{
	OEnemy::Controller();
	AttackState();
	
	if (ListBullet.size() >= maxBullet)
	{
		return;
	}
	if (timeAttack > reload)
	{
		timeAttack = 0;
		vector <Object*> listBullet;
		FuncItem::GetBullet(listBullet, this);

		D3DXVECTOR2 pos = _anim->GunPos(_enemyType + State + GetIndexGun());
		pos.x = isFlip ? -pos.x : pos.x;
		pos += position;

		for (size_t i = 0; i < listBullet.size(); i++)
		{
			OBullet* bullet = dynamic_cast<OBullet*>(listBullet[i]);
			bullet->Fire(pos);
			ListBullet.push_back(bullet);
		}
	}
}

void RifleMan::AttackState()
{
	D3DXVECTOR2 posPlayer = Player::GetInstance()->GetPosition();
	isFlip = posPlayer.x < position.x;

	AngleGun = 0;
	int range = 20;
	if (posPlayer.y > position.y + range)
	{
		if (abs(posPlayer.x - position.x) > range)
		{
			AngleGun = 45;
		}
		else AngleGun = 90;
	}
	else
		if (posPlayer.y < position.y - range)
		{
			if (abs(posPlayer.x - position.x) > range)
			{
				AngleGun = -45;
			}
			else AngleGun = -90;
		}
}

