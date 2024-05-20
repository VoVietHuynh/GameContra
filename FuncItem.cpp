#include "FuncItem.h"
#include "OBullet.h"
#include "ObjectManager.h"

FuncItem::FuncItem()
{

}
FuncItem::~FuncItem()
{

}

void FuncItem::CallFunc(int itemType)
{
	switch ((OItem::ItemType)itemType)
	{
	case OItem::R:
		Player::GetInstance()->_playerController->isReload = true;
		break;
	case OItem::M:
		Player::GetInstance()->GunType = itemType;
		Player::GetInstance()->maxBullet = 5;
		break;
	case OItem::S:
		Player::GetInstance()->GunType = itemType;
		Player::GetInstance()->maxBullet = 10;
		break;
	case OItem::F:
		Player::GetInstance()->GunType = itemType;
		Player::GetInstance()->maxBullet = 4;
		break;
	case OItem::L:
		Player::GetInstance()->GunType = itemType;
		Player::GetInstance()->maxBullet = 2;
		break;
	default:
		break;
	}
}
void FuncItem::GetBullet(std::vector<Object*>& listBullet, Object* obj)
{
	OItem::ItemType itemType = (OItem::ItemType)obj->GunType;
	int arrow = obj->AngleGun;
	int isFlip = obj->isFlip;

	int count = obj->maxBullet - obj->ListBullet.size();
	int num = GetNumBulletByType(itemType);
	count = num < count ? num : count;
	for (size_t i = 0; i < count; i++)
	{
		Object* bullet = CreateBullet(obj, arrow, isFlip, i, itemType);
		listBullet.push_back(bullet);
	}
}

Object* FuncItem::CreateBullet(Object* master, int arrow, bool isFlip, int index, int itemType)
{
	Object* obj = ObjectManager::GetInstance()->GetBullet();
	OBullet * bullet = dynamic_cast<OBullet*>(obj);
	int angleList[5] = { 0, 1, -1, 2, -2 };
	float acc = isFlip ? -1 : 1;
	int damage = 1;

	int bulletType = OBullet::NormalBullet;
	switch ((OItem::ItemType)itemType)
	{
	case OItem::M:
		acc *= 3;
		bulletType = OBullet::RedBullet;
		break;
	case OItem::S:
		acc *= 1.5;
		bulletType = OBullet::RedBullet;
		break;
	case OItem::F:
		damage = 2;
		bulletType = OBullet::FBullet;
		//delete bullet;
		//bullet = new OBullet();
		break;
	case OItem::L:
		damage = 4;
		acc *= 2;
		bulletType = OBullet::LBullet;
		break;
	case 10000:
		acc *= 0.5;
		bulletType = OBullet::EnemyBullet;
		break;
	default:
		acc *= 1.2;
		bulletType = OBullet::NormalBullet;
		break;
	}

	bullet->Init(arrow, acc, bulletType, angleList[index]);
	bullet->Master = master;
	bullet->Damage = damage;

	return bullet;
}

int FuncItem::GetNumBulletByType(int itemType)
{
	switch ((OItem::ItemType)itemType)
	{
	case OItem::S:
		return 5;
	default:
		break;
	}
	return 1;
}