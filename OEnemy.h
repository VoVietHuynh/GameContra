#include "Object.h"
#include "GameDefine.h"
#include "Collision.h"

using namespace Define;

class OEnemy : public Object
{
public:
	enum Enemytype
	{
		Soldier = 100,
		rifleman =  200,
	} _enemyType = Enemytype::Soldier;

	OEnemy();
	~OEnemy();

	void Init(D3DXVECTOR2 pos, int type = Enemytype::Soldier, int kind = 0);
	void BeforeUpdate(float gameTime, Keyboard* key);
	void Update(float gameTime, Keyboard* key);
	void UpdateAnimation(float gameTime);
	void Controller();
	D3DXVECTOR2 OnCollision(Object* obj, D3DXVECTOR2 side);
	void SetBound(float width, float height);
	void Render(Viewport* viewport);
	static Animation* GetAnimationEnemy();
};
