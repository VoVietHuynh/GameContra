#include "Game.h"
#include "debug.h"

Game::Game(HINSTANCE Hins, int width, int height, char* name)
{
	this->Hinsantance = Hins;
	this->Width = width;
	this->Height = height;
	this->Hwnd = NULL;
	strcpy_s(this->WindowName, name);
}

Game::~Game()
{
	delete graphic;
	keyboard->KillKeyboard();
	delete keyboard;
}

//Hàm xử lý cửa sổ
LRESULT CALLBACK Game::WindowProc(HWND Hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	if (Message == WM_DESTROY)
	{
		PostQuitMessage(0);
	}
	return DefWindowProc(Hwnd, Message, wParam, lParam);
}

//Tạo cửa sổ Game
bool Game::InitWD()
{
	WNDCLASSEX Wndclass;
	Wndclass.cbSize = sizeof(WNDCLASSEX);
	Wndclass.cbClsExtra = 0;
	Wndclass.cbWndExtra = 0;
	Wndclass.hIconSm = 0;
	Wndclass.hIcon = 0;
	Wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	Wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	Wndclass.hInstance = this->Hinsantance;
	Wndclass.lpfnWndProc = (WNDPROC)WindowProc;
	Wndclass.lpszClassName = this->WindowName;
	Wndclass.lpszMenuName = NULL;
	Wndclass.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&Wndclass))
	{
		return false;
	}

	this->Hwnd = CreateWindow(
		this->WindowName,
		this->WindowName, 
		WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT, 
		CW_USEDEFAULT, 
		this->Width, 
		this->Height, 
		NULL, NULL, 
		this->Hinsantance, 
		NULL);

	if (!this->Hwnd)
		return false;
	ShowWindow(this->Hwnd, SW_NORMAL);
	UpdateWindow(this->Hwnd);
	SetDebugWindow(this->Hwnd);
	//Tạo màn hình vẽ

	graphic = Graphic::GetInstance();
	graphic->Init(this->Hwnd, GameWidth, GameHeight);
	if (!graphic->InitD3D())
	{
		return false;
	}
	return true;
}

//Load Data Game
void Game::InitDT()
{
	keyboard = new Keyboard(Hwnd);
	keyboard->Init();
	SceneManager::GetInstance()->InitDT();
}

// Cập nhật game
void Game::Update(float gameTime)
{
	//Lấy trạng thái bàn phím
	keyboard->GetStage();
	SceneManager::GetInstance()->Update(gameTime, keyboard);
}

// Vẽ các đối tượng trong game
void Game::Render()
{
	graphic->Begin();
	SceneManager::GetInstance()->Render();
	graphic->End();
}
