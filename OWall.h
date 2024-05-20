#include "Object.h"
#include "GameDefine.h"
#include "Collision.h"

using namespace Define;

class OWall : public Object
{
public:
	enum Walltype
	{
		Wall = 100,
		Water = 200,
		Brigde = 300,
	} _walltype = Walltype::Wall;

	OWall();
	~OWall();

	void Init(D3DXVECTOR2 pos, int type = Walltype::Wall, int kind = 0);
	void BeforeUpdate(float gameTime, Keyboard* key);
	void Update(float gameTime, Keyboard* key);
	void UpdateAnimation(float gameTime);
	void Controller();
	D3DXVECTOR2 OnCollision(Object* obj, D3DXVECTOR2 side);
	RECT GetBound(float width, float height);
	RECT GetBound();
	void Render(Viewport* viewport);
};
