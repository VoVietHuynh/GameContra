#pragma once
#include "Object.h"
#include "PlayerCollision.h"
#include "PlayerController.h"
using namespace Define;

class OBullet;
class Player : public Object
{
private:
	static Player* _player;
public:
	enum PlayerType
	{
		Blue = 100,
		Red = 200,
	} _playerType;

	PlayerController* _playerController;
	PlayerCollision* _playerCollision;
	int _life;
	bool isImmortal = false;
	float immortalTime = 0;

	vector <OBullet*> ListBullet;
	vector <Object*> ItemBullet;
public:
	Player(); 
	~Player();

	void Init();
	void BeforeUpdate(float gameTime, Keyboard* key);
	void Update(float gameTime, Keyboard* key);
	void UpdateAnimation(float gameTime);
	void OnCollision(Object* obj, float gameTime);
	D3DXVECTOR2 OnCollision(Object* obj, D3DXVECTOR2 side);
	void OnCollision(Object* obj);
	void SetImmortal(float time);
	void SetBound(float width, float height);
	void Render(Viewport* viewport);
	static Player* GetInstance();
};
