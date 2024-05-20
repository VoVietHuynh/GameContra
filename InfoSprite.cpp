#include "InfoSprite.h"



InfoSprite::InfoSprite(const char* path)
{
	ReadXML(path);
}

InfoSprite::~InfoSprite()
{
}


void  InfoSprite::ReadXML(const char* path)
{
	//Lấy tài liệu xml
	TiXmlDocument doc(path);
	if (!doc.LoadFile())
	{
		MessageBox(NULL, path, "Error", MB_OK);
		return;
	}
	//Lấy thông tin thẻ
	TiXmlElement* sprite = doc.RootElement();
	TiXmlElement* indexml = nullptr;
	//Lấy thông tin kích thước sprite
	sprite->QueryFloatAttribute("width", &this->Width);
	sprite->QueryFloatAttribute("height", &this->Height);
	//Lấy kích thích frame mặc định
	sprite->QueryFloatAttribute("framew", &this->frameW);
	sprite->QueryFloatAttribute("frameh", &this->frameH);
	//Lấy thông tin từng index
	sprite->QueryIntAttribute("frame", &this->Frame);
	int n = 0;
	for (indexml = sprite->FirstChildElement(); indexml != NULL; indexml = indexml->NextSiblingElement())
	{
		//indexml->QueryIntAttribute("n", &n);
		float x, y, w, h, frameTime, sx, sy;
		std::string stateName;
		indexml->QueryFloatAttribute("x",  &x);
		indexml->QueryFloatAttribute("y", &y);
		indexml->QueryFloatAttribute("w", &w);
		indexml->QueryFloatAttribute("h", &h);
		//indexml->QueryFloatAttribute("frameTime", &frameTime);
		stateName = indexml->Attribute("id");
		indexml->QueryFloatAttribute("sx", &sx);
		indexml->QueryFloatAttribute("sy", &sy);
		this->_infoFrame[n] = { x, y, w, h, 100, stateName, sx, sy };
		n++;
	}
	int a = 1;
	//oke
}

float InfoSprite::GetWidth()
{
	return this->Width;
}

float InfoSprite::GetHeight()
{
	return this->Height;
}

float InfoSprite::GetFrameWidth()
{
	return this->frameW;
}

float InfoSprite::GetFrameHeight()
{
	return this->frameH;
}

RECT InfoSprite::GetRect(int Index)
{
	RECT rect;
	rect.left = _infoFrame[Index].x;	//x = IndexInfo[Index][0];
	rect.top = _infoFrame[Index].y;		//y = IndexInfo[Index][1];
	rect.right = rect.left + _infoFrame[Index].w;
	rect.bottom = rect.top + _infoFrame[Index].h;
	return rect;
}

InfoSprite::Infoframe InfoSprite::GetInfoByIndex(int index)
{
	return _infoFrame[index];
}