#pragma once
#include "Object.h"

class FuncItem
{
public:
	FuncItem();
	~FuncItem();

	static void CallFunc(int itemType);
	static void GetBullet(std::vector<Object*>& listBullet, Object* obj);
	static int GetNumBulletByType(int itemType);
	static Object* CreateBullet(Object* master, int arrow, bool isFlip, int index, int itemType = 0);
};

