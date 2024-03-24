#pragma once
#include "dinput.h"

namespace Define
{
	//Windows
	const float GameWidth = 256.0f;
	const float GameHeight = 240.0f;
	const float WinWidth = 768.0f;
	const float WinHeight = 720.0f;
	const float FPS = 60.0f;

	//Control
	const int Dik_SELECT = DIK_SPACE;
	const int Dik_START = DIK_RETURN;
	const int Dik_LEFT = DIK_LEFT;
	const int Dik_RIGHT = DIK_RIGHT;
	const int Dik_UP = DIK_UP;
	const int Dik_DOWN = DIK_DOWN;
	const int Dik_JUMP = DIK_Z;
	const int Dik_ATTACK = DIK_X;

	//Path
		//Player
	const char PlayerPNG[] = "./Resource Files/bill_animation.png";
	const char PlayerXML[] = "./Resource Files/player_info.xml";
		//Enemy
	const char EnemyPNG[] = "./Resource Files/Soldier.png";
	const char EnemyXML[] = "./Resource Files/enemy_info.xml";
		//Misc
	const char MiscPNG[] = "./Resource Files/misc_png.png";
	const char MiscXML[] = "./Resource Files/misc_info.xml";

		//Map
	const char TileSetPNG[] = "./Resource Files/TitleSetMap1.png";
	const char MapXML[] = "./Resource Files/Map1.tmx";

		

	//Player
	const int StartLive = 3;
	const float timeEnd = 3;

	//PlayerRun
	const float RunSpeed = 1.0f;
	const float Gravity = -1.75f;

	//Enemy
	const float EnemySpeed = 1.0f;
}