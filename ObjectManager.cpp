#include "ObjectManager.h"
#include "string.h"
#include "Player.h"
#include "OBullet.h"
#pragma warning(disable : 4996)


ObjectManager* ObjectManager::_objectManager;

ObjectManager* ObjectManager::GetInstance()
{
	if (nullptr == _objectManager) {
		_objectManager = new ObjectManager();
	}
	return _objectManager;
}

ObjectManager::ObjectManager()
{
	viewport = new Viewport(0, 0);
}
ObjectManager::~ObjectManager()
{
	delete map;
	delete viewport;
}

//Load Data Game
void ObjectManager::InitDT()
{
	//load Objecct
	if (map != nullptr)
	{
		delete map;
		map = NULL;
	}
	map = new Map();
}

//Update Game
void ObjectManager::Update(float gameTime, Keyboard* key)
{
	fixTime += gameTime;
	IsFixTime = false;
	if (fixTime > 0.05)
	{
		IsFixTime = true;
		fixTime = 0;
	}
	//
	if (key->IsKeyDown(Dik_START))
	{
		float time = std::numeric_limits<float>::infinity();
		if (isPause)
			StartPause(0);
		else
			StartPause(time);
	}

	//checkPause
	if (isPause)
	{
		if (pauseTime > 0)
			pauseTime -= gameTime;
		else
			isPause = false;
		return;
	}
	vector <Object*> listObject;
	//map->ListObject.clear();
	//map->Tree->getObjectsCollideAble(mCurrList, viewport->GetBoundViewport());
	for (size_t i = 0; i < map->ListObject.size(); i++)
	{
		Object* obj = map->ListObject.at(i);
		if (Collision::isCollision(obj->GetBound(), viewport->GetBoundViewport1())
			|| obj->Tag == Object::Player)
		{
			listObject.push_back(obj);
			obj->BeforeUpdate(gameTime, key);
		}

	}

	//Check Collision
	for (size_t i = 0; i < listObject.size(); i++)
	for (size_t j = 0; j < listObject.size(); j++)
		if (i != j)
			listObject.at(i)->OnCollision(listObject.at(j), gameTime);

	//Update all Object
	for (size_t i = 0; i < listObject.size(); i++)
		listObject.at(i)->Update(gameTime, key);

	//Update Viewport theo vị trí Player
	if (Player::GetInstance()->State != Object::Dying)
	viewport->Update(gameTime, key, Player::GetInstance()->GetPosition());
}

void ObjectManager::StartPause(float time)
{
	isPause = true;
	pauseTime = time;
}

void ObjectManager::AddObjectMap(Object* obj)
{
	map->ListObject.push_back(obj);
}

void ObjectManager::DeleteObjectMap(Object* obj)
{
	auto it = std::find(map->ListObject.begin(), map->ListObject.end(), obj);
	if (it != map->ListObject.end())
	{
		map->ListObject.erase(it);
	}
}

bool ObjectManager::TryDeleteObject(Object* obj)
{
	if (Collision::isCollision(obj->GetBound(), viewport->GetBoundViewport()))
	{
		return false;
	}
	DeleteObjectMap(obj);
	return true;
}

Object* ObjectManager::GetBullet()
{
	int maxB = 30;
	if (mBulletList.size() > maxB)
	{
		currBullet++;
		if (currBullet >= mBulletList.size()) currBullet = 0;
		return mBulletList[currBullet];
	}

	OBullet* bullet = new OBullet();
	mBulletList.push_back(bullet);
	return bullet;
}

Viewport* ObjectManager::GetViewPort()
{
	return viewport;
}

//Vẽ
void ObjectManager::Render()
{
	//Vẽ map
	map->Render(viewport);
	//Vẽ
	for (size_t i = 0; i < map->ListObject.size(); i++)
	{
		map->ListObject.at(i)->Render(viewport);
		DrawLine::GetInstance()->SetColor(map->ListObject.at(i)->Tag*70, map->ListObject.at(i)->type * 50, map->ListObject.at(i)->_kind * 80);
		DrawLine::GetInstance()->DrawRect(map->ListObject.at(i)->GetBound());
	}

	//GUI
	GUI::GetInstance()->Render();
}