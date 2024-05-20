#pragma once
#include <d3dx9.h>
#include "string"
#include "map"
#include "TinyXML\tinyxml.h"
class InfoSprite
{
public:
	struct Infoframe
	{
		float x;
		float y;
		float w;
		float h;
		float frameTime;
		std::string stateName;
		float sx;
		float sy;
	};
protected:
	float Width, Height ,frameW , frameH;
	int Frame;
	typedef std::map<int, Infoframe> InfoFrame;
	InfoFrame _infoFrame;
public:
	InfoSprite(const char* path);
	~InfoSprite();

	float GetWidth();
	float GetHeight();
	float GetFrameWidth();
	float GetFrameHeight();

	void ReadXML(const char* path);
	RECT GetRect(int Index);
	Infoframe GetInfoByIndex(int index);
};

