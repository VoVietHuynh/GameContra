#include <Windows.h>
#include "Game.h"
#include "GameDefine.h"
#include "debug.h"
using namespace Define;

int WINAPI WinMain(HINSTANCE Hins, HINSTANCE HIns, LPTSTR a, int c)
{
	MSG Msg;
	//Khai báo Object game
	Game game(Hins, WinWidth, WinHeight, "ContraNes");
	if (!game.InitWD())
	{
		MessageBox(NULL, "Can't load Init Game", "Error", MB_OK);
		return 0;
	}

	//Load Data 
	game.InitDT();
	//Biến thời gian
	LARGE_INTEGER startTime;
	double frequence;
	float frameTime = 1.0f / FPS;
	float gameTime = 0;
	LARGE_INTEGER endTime;
	float delay = 0;
	ZeroMemory(&Msg, sizeof(Msg));
	QueryPerformanceFrequency(&startTime);//Hàm trả gái trị đúng
	frequence = double(startTime.QuadPart);
	QueryPerformanceCounter(&startTime);

	//Render
	while (Msg.message != WM_QUIT)
	{
		if (PeekMessage(&Msg, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
		else
		{
			QueryPerformanceCounter(&endTime);
			gameTime = double(endTime.QuadPart - startTime.QuadPart) / frequence;
			if (gameTime < frameTime)
			{
				Sleep((frameTime - gameTime) * 1000);//Ngủ theo second
				gameTime = frameTime;
			}
			QueryPerformanceCounter(&startTime);
			game.Update(gameTime);
			game.Render();
		}
	}
	return 0;
}