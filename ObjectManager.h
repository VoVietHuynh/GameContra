#pragma once
#include <vector>
#include "Graphic.h"
#include "Keyboard.h"
#include "GUI.h"
#include "Viewport.h"
#include "Collision.h"
#include "Map.h"

using namespace Define;

class ObjectManager
{
private:
	static ObjectManager* _objectManager;
protected:
	Viewport* viewport;
	Map* map;

	float pauseTime, fixTime;
	vector <Object*> mCurrList;

public:
	bool isPause;
	bool IsFixTime = false;

	vector <Object*> mBulletList;
	int currBullet;

	ObjectManager();
	~ObjectManager();

	static ObjectManager* GetInstance();
	//Load Data Game
	void InitDT();

	void Update(float gameTime, Keyboard* key);
	void StartPause(float time);
	Viewport* GetViewPort();
	void AddObjectMap(Object* obj);
	void DeleteObjectMap(Object* obj);
	bool TryDeleteObject(Object* obj);
	//Vẽ Object lên màn hình
	void Render();

	Object* GetBullet();
};
