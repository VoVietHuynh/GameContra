#pragma once
#include "Viewport.h"
#include "Animation.h"
#include "Collision.h"
#include "DrawLine.h"

class Object
{
protected:
	Animation* _anim;
	float Width, Height;
	bool AllowDraw, lock;
	D3DXVECTOR2 position; //vị trí vẽ
	D3DXVECTOR2 velocity;//Vector vận tốc
	D3DXVECTOR2 transform;
	float angle;
	RECT bound;
	int HP = 0, Damage = 0;
	string name;
public:
	D3DXVECTOR2 positionStart;
	//Jump
	bool isFlip;
	bool isAllowJump = true, isFall = false;
	float posYStartJump, velYStartFall, gravity, speedJump, maxJump;
	float timeDead;
public:
	int id;
	int _kind = 0;
	int type;
	enum tag
	{
		Wall,
		Player,
		Enemy,
		Bullet
	}Tag;

	enum Stateobject
	{
		Standing = 0,
		Running = 10,
		Jumping = 20,
		Attacking = 30,
		Sitting = 40,
		Dying = 50,
		Swimming = 60,
		Diving = 70,
	};
	Stateobject State;
	Object();
	~Object();
	virtual void Init(D3DXVECTOR2 pos, int _type = 0, int kind = 0);
	static tag GetTag(string name);
	void SetTag(tag name);
	Stateobject GetState();
	void SetState(Stateobject _stateObject);
	virtual bool GetFlipFlag();
	virtual void SetFlipFlag(bool flag);
	//Khung va chạm
	virtual RECT GetBound();
	virtual RECT GetBound(float width, float height);
	virtual void SetBound(RECT bound);

	//Thông tin frame
	virtual float GetWidth();
	virtual void SetWidth(float width);
	virtual float GetHeight();
	virtual void SetHeight(float height);

	//Vị trí
	virtual D3DXVECTOR2 GetPosition();
	virtual D3DXVECTOR2 GetPositionStart();
	virtual void SetPosition(D3DXVECTOR2 Position);
	virtual void SetPositionStart(D3DXVECTOR2 Position);
	virtual void SetPositionX(float x);//lấy vị trí từ bound sau khi va chạm
	virtual void SetPositionY(float y);

	//Vận tốc
	virtual D3DXVECTOR2 GetVelocity();
	virtual void SetVelocity(D3DXVECTOR2 Velocity);
	virtual void SetVelocityX(float x);
	virtual void SetVelocityY(float y);
	virtual void SetVelocity(float x, float y);

	//Dịch chuyển
	virtual D3DXVECTOR2 GetTransform();
	virtual void SetTransform(D3DXVECTOR2 Transform);
	virtual void SetTransform(float x, float y);

	//Góc
	virtual float GetAngle();
	virtual void SetAngle(float Angle);

	//Tính khoảng cách trong khoảng time
	virtual D3DXVECTOR2 Distance(float time);

	//cho phép vẽ
	virtual void SetAllowDraw(bool allowDraw);
	virtual bool GetAllowDraw();

	//Máu
	virtual void SetHP(int hp);
	virtual int GetHP();
	//Damage
	virtual void SetDamage(int damage);
	virtual int GetDamage();

	virtual void LockAnimation(bool lock, int index);

	virtual bool Die();
	virtual void Controller();
	virtual void BeforeUpdate(float gameTime, Keyboard* key);
	virtual void Update(float gameTime, Keyboard* key);
	virtual void UpdateAnimation(float gameTime);
	virtual void Render(Viewport* viewport);
	// va cham
	virtual void OnCollision(Object* obj, float gameTime);
	virtual void OnCollision(Object* obj);
	virtual D3DXVECTOR2 OnCollision(Object* obj, D3DXVECTOR2 side);
	RECT GetBoard(D3DXVECTOR2 distance);
	virtual void SetName(string name) { this->name = name; }
	virtual string GetName() { return name; }
	virtual void AddVelocity(float x, float y)
	{
		velocity.x += x;
		velocity.y += y;
	}
};

