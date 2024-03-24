#pragma once
#include <Windows.h>
#include "Graphic.h"
#include "Keyboard.h"
#include "SceneManager.h"
#include "GameDefine.h"

using namespace Define;

class Game
{
private:
	//HINSTANCE của chương trình 
	HINSTANCE Hinsantance;
	//HWND của của sổ
	HWND Hwnd;
	//Kích thước cửa sổ
	int Width;
	int Height;
	//Tên cửa sổ
	char WindowName[256];
	//Xử lý cửa sổ
	static HRESULT CALLBACK WindowProc(HWND Hwnd, UINT Message, WPARAM wParam, LPARAM lParam);

	//Khai báo đối tượng graphic
	Graphic* graphic;
	//Khai báo đối tượng Keyboard
	Keyboard* keyboard;
public:
	Game(HINSTANCE Hins, int width, int height, char* name);
	~Game();
	//Thiết lập các giá trị cho cửa sổ
	bool InitWD();
	//Load Data Game
	void InitDT();
	//Update Game sau khoảng thời gian gameTime
	void Update(float gameTime);
	//Vẽ Object lên màn hình
	void Render();
	//
};

