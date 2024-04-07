#include "ObjectManager.h"
#include "string.h"
#include "Player.h"
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

	//map->ListObject.clear();
	//map->Tree->getObjectsCollideAble(map->ListObject, viewport->GetBoundViewport());

	//BeforeUpdate all Object
	for (size_t i = 0; i < map->ListObject.size(); i++)
	{
		map->ListObject.at(i)->BeforeUpdate(gameTime, key);
	}

	//Check Collision
	for (size_t i = 0; i < map->ListObject.size(); i++)
	for (size_t j = 0; j < map->ListObject.size(); j++)
		if (i != j)
			map->ListObject.at(i)->OnCollision(map->ListObject.at(j), gameTime);

	//Update all Object
	for (size_t i = 0; i < map->ListObject.size(); i++)
		map->ListObject.at(i)->Update(gameTime, key);

	//Update Viewport theo vị trí Player
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
		DrawLine::GetInstance()->DrawRect(map->ListObject.at(i)->GetBound());
	}

	//GUI
	GUI::GetInstance()->Render();
}