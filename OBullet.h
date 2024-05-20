#include "Object.h"
#include "GameDefine.h"
#include "Collision.h"

using namespace Define;

class OBullet : public Object
{
public:
	bool IsFire = false;
	float Angle = 0;
	D3DXVECTOR2 localPosition;
	float time = 0;
	Object* Master;
	void DeleteBullet()
	{
		if (Master == NULL) return;
		auto it = std::find(Master->ListBullet.begin(), Master->ListBullet.end(), this);
		if (it != Master->ListBullet.end())
		{
			Master->ListBullet.erase(it);
		}
	}
	enum Bullettype
	{
		NoneBullet = 100,
		NormalBullet = 200,
		RedBullet = 300,
		FBullet = 400,
		LBullet = 500,
		EnemyBullet = 600,
	} _bulletType = Bullettype::NoneBullet;

	OBullet();
	~OBullet();

	void Init(int angle, float acceleration, D3DXVECTOR2 pos, int type = Bullettype::NoneBullet, int kind = 0);
	void Init(int angle, float acceleration, int type = Bullettype::NoneBullet, int kind = 0);
	void Reset();
	void Fire(D3DXVECTOR2 pos);
	void BeforeUpdate(float gameTime, Keyboard* key);
	void Update(float gameTime, Keyboard* key);
	void UpdateAnimation(float gameTime);
	void Controller();
	D3DXVECTOR2 OnCollision(Object* obj, D3DXVECTOR2 side);
	void OnCollision(Object* obj);
	void SetBound(float width, float height);
	void Render(Viewport* viewport);
	static Animation* GetAnimationBullet();
};
