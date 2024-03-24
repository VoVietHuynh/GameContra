#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
using namespace std;

class Graphic
{
private:
	static Graphic* _graphic;
private:
	//Object directx
	LPDIRECT3D9 D3D;
	//
	LPDIRECT3DDEVICE9 D3Ddev;
	//Font
	ID3DXFont *mFont;
	//Surface
	LPDIRECT3DSURFACE9 Backbuffer;
	LPDIRECT3DSURFACE9 Surface;
	D3DPRESENT_PARAMETERS D3DPP;

	LPD3DXSPRITE D3Dsprite;
	//Vẽ texture Sprite Handal
	LPD3DXSPRITE SpriteHandler;
	//HWND của texture
	HWND HwndS;
	//Kích thước
	int Width;
	int Height;

public:
	//Contructor
	Graphic();
	void Init(HWND hwnd, int width, int height);
	~Graphic();
	//Cài đặt thiết kế vẽ
	bool InitD3D();
	//Bắt đầu vẽ
	void Begin();
	//Kết thúc vẽ
	void End();
	//Load 1 Texture
	LPDIRECT3DTEXTURE9 LoadTexture(string path, D3DCOLOR);
	//Load 1 Surface
	LPDIRECT3DSURFACE9 LoadSurface(string path, D3DCOLOR);
	//Vẽ các hình
	void DrawTexture(LPDIRECT3DTEXTURE9 texture, RECT source, D3DXVECTOR2 center, D3DXVECTOR2 position, D3DCOLOR color);
	void DrawTexture(LPDIRECT3DTEXTURE9 texture, RECT source, D3DXVECTOR2 center, D3DXVECTOR2 position, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DCOLOR color);//Vẽ tự do
	void DrawString(char* text, RECT r, D3DCOLOR color);
	//Vẽ các surface
	void DrawSurface();
	//Lấy thiết bị vẽ
	LPDIRECT3DDEVICE9 GetDevice();
	HWND GetHwnd();
	LPD3DXSPRITE GetSprite();
	static Graphic* GetInstance();
};

