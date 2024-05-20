#include "Animation.h"

Animation::Animation(const char* pathInfo, const char* pathPNG):Sprite(pathPNG)
{
	_infoAnim = new InfoSprite(pathInfo);
	delay = 0;
	start = 0;
	end = 0;
	scale = D3DXVECTOR2(1, 1);
	position = D3DXVECTOR2(0, 0);
	FlipFlag = false;
	angle = 0;
	Pause = false;
}

Animation::Animation()
{
	start = 0;
	end = 0;
	scale = D3DXVECTOR2(1, 1);
	position = D3DXVECTOR2(0, 0);
	FlipFlag = false;
	angle = 0;
}

Animation::~Animation()
{
	delete _infoAnim;
}

void Animation::SetFrame(D3DXVECTOR2 Position, bool Flip, int Delay, int Start, int End)
{
	position = Position;
	FlipFlag = Flip;
	delay = Delay;
	start = Start;
	end = End;
	Index = Start;
}

void Animation::SetDataAnimation(DataAnimMap data)
{
	_dataAnim = data;
}

void Animation::NewAnimationByIndex(int index)
{
	DataAnim data = _dataAnim[index];
	start = data.start;
	end = data.end;
	delay = data.delay;
}

int Animation::GetIndex()
{
	return Index;
}
void Animation::SetIndex(int index)
{
	Index = index;
}

//Rect
RECT Animation::GetRectByIndex(int index)
{
	return _infoAnim->GetRect(index);
}

InfoSprite::Infoframe Animation::GetCurrentFrameInfo()
{
	return _infoAnim->GetInfoByIndex(Index);
}

bool Animation::GetFlipFlag()
{
	return FlipFlag;
}

int Animation::GetDelay()
{
	return delay;
}

int Animation::GetStart()
{
	return start;
}

int Animation::GetEnd()
{
	return end;
}

void Animation::SetPause(bool pause)
{
	Pause = pause;
}
void Animation::SetPause(bool pause, int index)
{
	IndexPause = index;
	Pause = pause;
}

void Animation::Update(float gameTime)
{
	//Chuyển frame tiếp theo
	if (TimeCurrent * 1000 >= delay )
	{
		TimeCurrent = 0;
		Index++;
	}
	else TimeCurrent += gameTime;
	//Lấy giá trị Index để vẽ Rect
	if (Index < start || Index > end)
	{
		Index = start;
	}
	//Kiểm tra Frame dừngz
	if (Pause)
	{
		Index = IndexPause;
	}
	//Kiểm tra Flip
	Flip(FlipFlag);
	//Set rect mới
	SetRect(GetRectByIndex(Index));
	//Lấy center
	center.x = (rect.right - rect.left)/2;
	center.y = (rect.bottom - rect.top) / 2;
	////Kiểm tra center flip chỉnh transform
	transform.x = 0;
	transform.y = 0;
}

D3DXVECTOR2 Animation::GunPos(int index)
{
	auto config = _infoAnim->GetInfoByIndex(_dataAnim[index].start);
	if (config.sx != 0)
		return D3DXVECTOR2(config.sx, config.sy);
	return D3DXVECTOR2(0, 0);
}