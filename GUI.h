#pragma once
#include "DrawString.h"
#include "Graphic.h"
#include "Player.h"

class GUI
{
private:
	static GUI* _gui;

protected:
	DrawString *gui;
public:
	GUI();
	~GUI();
	void Render(const char* text, RECT rect);
	void Render(int num, RECT rect);
	void Render();
	static GUI* GetInstance();
};

