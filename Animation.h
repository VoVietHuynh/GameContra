#pragma once
#include "Sprite.h"
#include "InfoSprite.h"
#include "map"
#include "debug.h"


class Animation : public Sprite
{
public:
	struct DataAnim{
		int start, end, delay = 100 , state;
	};
	typedef map<int, DataAnim> DataAnimMap;

public:
	InfoSprite* _infoAnim;
	DataAnimMap _dataAnim;
	float TimeCurrent;
	int delay, start, end, IndexPause;
	bool Pause;
	int Index = 0;
public:
	Animation(const char* pathInfo, const char* pathPNG);
	Animation();
	~Animation();
	//Set thông số để vẽ 
	void SetFrame(D3DXVECTOR2 Position, bool Flip, int Delay, int Start, int End);

	void SetDataAnimation(DataAnimMap dataAnim);
	void NewAnimationByIndex(int index);

	int GetIndex();
	void SetIndex(int index);
	RECT GetRectByIndex(int index);
	InfoSprite::Infoframe GetCurrentFrameInfo();
	bool GetFlipFlag();
	int GetDelay();
	int GetStart();
	int GetEnd();
	void SetPause(bool pause);
	void SetPause(bool, int);
	void Update(float gameTime);
};
