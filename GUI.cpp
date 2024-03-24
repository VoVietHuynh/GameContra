#include "GUI.h"
#include "string.h"
#pragma warning(disable : 4996)

GUI* GUI::_gui = nullptr;

GUI* GUI::GetInstance()
{
	if (nullptr == _gui) {
		_gui = new GUI();
	}
	return _gui;
}

GUI::GUI()
{
	gui = new DrawString(Graphic::GetInstance(), 12);
}

GUI::~GUI()
{
	delete gui;
}

void GUI::Render(const char* text, RECT rect)
{
	char _text[10];
	strcpy(_text, text);
	gui->Render(_text, rect, D3DCOLOR_XRGB(255, 255, 255));
}

void GUI::Render(int num, RECT rect)
{
	char _text[10];
	itoa(num, _text, 10);
	gui->Render(_text, rect, D3DCOLOR_XRGB(255, 255, 255));
}

//Vẽ
void GUI::Render()
{
}