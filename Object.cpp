#include "Object.h"
#include "OWall.h"
#include "Player.h"

Object::Object()
{
	AllowDraw = true;
}

Object::~Object()
{
}

void Object::Init(D3DXVECTOR2 pos, int _type, int kind)
{
}


bool Object::GetFlipFlag()
{
	return FlipFlag;
}
void Object::SetFlipFlag(bool flag)
{
	FlipFlag = flag;
}
//Khung va chạm
RECT Object::GetBound()
{
	return bound;
}
void Object::SetBound(RECT bound)
{
	this->bound = bound;
}
//position ở x, y ở giữa
RECT Object::GetBound(float width, float height)
{
	Width = width;
	Height = height;
	bound.left = position.x - width / 2;
	bound.right = bound.left + width;
	bound.top = position.y + height/2;
	bound.bottom = bound.top - height;
	return bound;
}

//Thông tin frame
float Object::GetWidth()
{
	return this->Width;
}
void Object::SetWidth(float width)
{
	this->Width = width;
}
float Object::GetHeight()
{
	return this->Height;
}
void Object::SetHeight(float height)
{
	this->Height = height;
}


//Vị trí
D3DXVECTOR2 Object::GetPosition()
{
	return position;
}
D3DXVECTOR2 Object::GetPositionStart()
{
	return positionStart;
}
void Object::SetPosition(D3DXVECTOR2 Position)
{
	position = Position;
}
void Object::SetPositionStart(D3DXVECTOR2 Position)
{
	position = Position;
	positionStart = Position;
}
void Object::SetPositionX(float x)
{
	position.x = x;
}
void Object::SetPositionY(float y)
{
	position.y = y;
}

//Vận tốc
D3DXVECTOR2 Object::GetVelocity()
{
	return velocity;
}
void Object::SetVelocity(D3DXVECTOR2 Velocity)
{
	velocity = Velocity;
}
void Object::SetVelocityX(float x)
{
	velocity.x = x;
}
void Object::SetVelocityY(float y)
{
	velocity.y = y;
}
void Object::SetVelocity(float x, float y)
{
	velocity.x = x;
	velocity.y = y;
}

//Dịch chuyển
D3DXVECTOR2 Object::GetTransform()
{
	return transform;
}
void Object::SetTransform(D3DXVECTOR2 Transform)
{
	transform = Transform;
}
void Object::SetTransform(float x, float y)
{
	transform.x = x;
	transform.y = y;
}

//Góc
float Object::GetAngle()
{
	return angle;
}
void Object::SetAngle(float Angle)
{
	angle = Angle;
}

//Khoảng cách
D3DXVECTOR2 Object::Distance(float time)
{
	return velocity * 100 * time;
}


//cho phép vẽ
void Object::SetAllowDraw(bool allowDraw)
{
	AllowDraw = allowDraw;
}
bool Object::GetAllowDraw()
{
	return AllowDraw;
}

//Máu
void Object::SetHP(int hp)
{
	HP = hp;
}
int Object::GetHP()
{
	return HP;
}

//Máu
void Object::SetDamage(int damage)
{
	Damage = damage;
}
int Object::GetDamage()
{
	return Damage;
}

void Object::LockAnimation(bool Lock, int index)
{

}

//Kiểm tra chết chưa
bool Object::Die()
{
	if (HP <= 0)
		return true;
	else
		return false;
}

void Object::Controller()
{
}
void Object::BeforeUpdate(float gameTime, Keyboard* key)
{
}

void Object::Update(float gameTime, Keyboard* key)
{
	velocity.y *= timeCollisionMin;
	position += velocity * gameTime * 100;
	timeCollisionMin = 1.0f;
}

void Object::UpdateAnimation(float gameTime)
{
}

void Object::OnCollision(Object *obj, float gameTime)
{
	if (obj->State == Object::Dying || this->State == Object::Dying)
		return;
	D3DXVECTOR2 side;
	D3DXVECTOR2 distance = velocity * gameTime * 100;
	RECT board = GetBoard(distance);
	//Nếu obj trong vùng di chuyển
	if (Collision::isCollision(board, obj->GetBound()))
	{
		if (!Collision::isCollision1(GetBound(), obj->GetBound()))
		{
			//lấy thời gian va chạm
			float Time = Collision::CollisionAABB(GetBound(), obj->GetBound(), distance, side);

			//bé hơn 1 thì có va chạm
			if (Time < 1.0f)
			{
				if (obj->Tag == Object::Wall) //Nếu là tường đi xuyên
				{
					//Nếu là tường đi xuyên
					if (dynamic_cast<OWall*>(obj)->_walltype == OWall::Wall && obj->_kind == 0)
					{
						//Đụng đáy thì đi lên tường
						if (side.y == Collision::BOTTOM)
							side = D3DXVECTOR2(Collision::NONE, side.y);
						else
						{
							side = D3DXVECTOR2(Collision::NONE, Collision::NONE);
							return;
						}
					}
				}
				side = OnCollision(obj, side);
				//Chạm trục nào update rồi cho vận tốc bằng không
				if (side.x != Collision::NONE)
				{
					position.x += distance.x * Time;
					velocity.x = 0;
				}
				else if (side.y == Collision::BOTTOM)
				{
					position.y += distance.y * Time;
					velocity.y = 0;
				}
				else if (side.y != Collision::NONE)
				{
					timeCollisionMin = Time < timeCollisionMin ? Time : timeCollisionMin;
				}
			}
		}
		else OnCollision(obj);
	}
}

//Nếu lồng nhau
void Object::OnCollision(Object* obj)
{
}

//if bằng true thì dừng
D3DXVECTOR2 Object::OnCollision(Object* obj, D3DXVECTOR2 side)
{
	return side;
}

void Object::Render(Viewport* viewport)
{
}
RECT Object::GetBoard(D3DXVECTOR2 distance)
{
	return Collision::GetBoard(this->GetBound(), distance);
}
Object::tag Object::GetTag(string name)
{
	if (name == "Player")
	{
		return tag::Player;
	}
	if (name == "Wall" || name == "Water")
	{
		return tag::Wall;
	}
	if (name == "Soldier")
	{
		return tag::Enemy;
	}
	return tag::Wall;
}

void Object::SetTag(Object::tag _tag)
{
	Tag = _tag;
}

Object::Stateobject Object::GetState()
{
	return State;
}

void Object::SetState(Stateobject _stateObject)
{
	State = _stateObject;
}
