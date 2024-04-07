#include "Object.h"
#include "GameDefine.h"
#include "Collision.h"

using namespace Define;

class OBullet : public Object
{
public:
	enum Bullettype
	{
		NoneBullet = 100,
		NormalBullet = 200,
	} _bulletType = Bullettype::NoneBullet;

	OBullet();
	~OBullet();

	void Init(int acceleration, D3DXVECTOR2 pos, int type = Bullettype::NoneBullet, int kind = 0);
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
