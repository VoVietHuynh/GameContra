#pragma once
#include "Graphic.h"
#include "Keyboard.h"
#include "ObjectManager.h"
#include "GameDefine.h"

using namespace Define;

class SceneManager
{
static SceneManager* _sceneManager;

public:
	bool isEnd;
	float endTime;

public:
	SceneManager();
	~SceneManager();

	//Load Data Game
	void InitDT();

	//Update Game sau khoảng thời gian gameTime
	void Update(float gameTime, Keyboard* key);
	void StartEnd(float time = timeEnd);
	//Vẽ Object lên màn hình
	void Render();
	static SceneManager* GetInstance();
};

