#include "Graphic.h"

Graphic* Graphic::_graphic = nullptr;

Graphic::Graphic()
{
}

void Graphic::Init(HWND hind, int width, int height)
{
	this->HwndS = hind;
	this->Width = width;
	this->Height = height;
	this->D3D = NULL;
	this->D3Ddev = NULL;
	this->D3Dsprite = NULL;
	this->mFont = NULL;
	sound = new Sound(hind);
	sound->Init_DirectSound();
}

Graphic::~Graphic()
{
}

Graphic* Graphic::GetInstance()
{
	if (nullptr == _graphic) {
		_graphic = new Graphic(); 
	}
	return _graphic;
}

//Cài đặt thiết kế vẽ
bool Graphic::InitD3D()
{
	//Tạo Object Direct3D
	this->D3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (!this->D3D)
	{
		return false;
	}
	//Tạo thiết bị vẽ
	ZeroMemory(&D3DPP, sizeof(D3DPP));
	D3DPP.BackBufferCount = 1;
	D3DPP.BackBufferFormat = D3DFMT_UNKNOWN;//Tạo Format phù hợp
	D3DPP.BackBufferWidth = this->Width;
	D3DPP.BackBufferHeight = this->Height;
	D3DPP.hDeviceWindow = this->HwndS;//Handle cửa sổ cần vẽ lên
	D3DPP.SwapEffect = D3DSWAPEFFECT_DISCARD;//Tham số hay dùng
	D3DPP.Windowed = true;//Chế độ có cửa sổ
	//CreateDevice(Thiết bị vẽ mặc định, Hỗ trợ phần cứng, Cửa sổ vẽ, (Không rõ), Thông số BlackBuffer, Con trỏ nhận dữ liệu sai khi tạo Device);
	HRESULT hr = this->D3D->CreateDevice(
		D3DADAPTER_DEFAULT, 
		D3DDEVTYPE_HAL, 
		this->HwndS, 
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
		&D3DPP, 
		&this->D3Ddev);

	if (FAILED(hr))
	{
		return false; //false nếu thất bại
	}
	//Tạo các Texture

	hr = D3DXCreateSprite(this->D3Ddev, &this->D3Dsprite);
	if (FAILED(hr))
	{
		return false;
	}

	//Tạo Font
	hr = D3DXCreateFont(this->D3Ddev,    // the D3D Device
		12,  // font height
		0,    // default font width
		FW_NORMAL,    // font weight
		1,    // not using MipLevels
		false,    // italic font
		DEFAULT_CHARSET,    // default character set
		OUT_DEFAULT_PRECIS,    // default OutputPrecision,
		DEFAULT_QUALITY,    // default Quality
		DEFAULT_PITCH | FF_DONTCARE,    // default pitch and family
		"Times New Roman",    // use Facename Arial
		&mFont);

	if (FAILED(hr))
	{
		return false;
	}

	return true;
}
LPDIRECT3DTEXTURE9 Graphic::LoadTexture(string path, D3DCOLOR transcolor)
{
	LPDIRECT3DTEXTURE9 texture = NULL;
	D3DXIMAGE_INFO info;
	HRESULT hr;
	ZeroMemory(&info, sizeof(info));
	//Lấy thông tin về hình ảnh
	hr = D3DXGetImageInfoFromFile(path.c_str(), &info);
	if (hr != D3D_OK)
	{
		return NULL;
	}
	//Tạo Texture
	hr = D3DXCreateTextureFromFileEx(
		this->D3Ddev,
		path.c_str(),
		info.Width,
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN, //Tự chọn Fomat phù hợp
		D3DPOOL_DEFAULT,//Lớp bộ nhớ cho texture
		D3DX_DEFAULT,	//Bộ lọc hình ảnh
		D3DX_DEFAULT,	//Bộ lọc mip
		transcolor, //Chỉ ra màu trong suốt
		&info,	//Thông tin ảnh
		NULL, //Đổ màu
		&texture);

	if (hr != D3D_OK)
	{
		return 0;
	}
	return texture;
}

//Load 1 Surface
PDIRECT3DSURFACE9 Graphic::LoadSurface(string path, D3DCOLOR transcolor)
{
	PDIRECT3DSURFACE9 surface = NULL;
	D3DXIMAGE_INFO info;
	HRESULT hr;
	ZeroMemory(&info, sizeof(info));
	hr = D3DXGetImageInfoFromFile(path.c_str(), &info);

	if (hr != D3D_OK)
	{
		return NULL;
	}
	//Tạo Surface
	hr = this->D3Ddev->CreateOffscreenPlainSurface(
		info.Width,
		info.Height,
		D3DFMT_X8R8G8B8, //surface format
		D3DPOOL_DEFAULT,//Bộ nhớ lưu tự động
		&Surface,	//Con trỏ lưu surface được tạo ra
		NULL);

	if (hr != D3D_OK)
	{
		return 0;
	}

	hr = D3DXLoadSurfaceFromFile(
		surface,
		NULL,
		NULL,
		path.c_str(),
		NULL,
		D3DX_DEFAULT,
		transcolor,
		NULL);

	if (hr != D3D_OK)
	{
		return 0;
	}
	return surface;
}

void Graphic::Begin()
{
	//Vẽ cửa sổ vẽ bằng màu đen (156, 252, 240) màu xanh
	this->D3Ddev->Clear(1, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(156, 252, 240), 0, NULL);
	//Bắt đầu vẽ
	
	this->D3Ddev->BeginScene();
	this->D3Dsprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void Graphic::End()
{
	//Kết thúc vẽ
	this->D3Dsprite->End();
	this->D3Ddev->EndScene();
	//Thể hiện tương đối các đối tượng BlackBuffer ra ngoài màn hình
	this->D3Ddev->Present(NULL, NULL, NULL, NULL);
}

//Vẽ các hình
//Draw(Hình cần vẽ, Khung cắt từ ảnh(NULL lấy hết texture), Tâm texture(NULL là 0,0), Tọa độ texture trên màn hình đồ họa, Màu texture);
void Graphic::DrawTexture(LPDIRECT3DTEXTURE9 texture, RECT source, D3DXVECTOR2 center, D3DXVECTOR2 position, D3DCOLOR color)
{
	this->D3Dsprite->Draw(texture, &source, &D3DXVECTOR3(center.x, center.y, 0), &D3DXVECTOR3(position.x, position.y, 0), color);
}

//Vẽ tự do
void Graphic::DrawTexture(LPDIRECT3DTEXTURE9 texture, RECT source, D3DXVECTOR2 center, D3DXVECTOR2 position, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DCOLOR color)
{
	//Vẽ theo thông số cho trước
	D3DXVECTOR2 CenterMatrix = position;
	float rad = angle * (3.14159265358979323846 / 180);
	D3DXMATRIX matrix; //Ma trận biến đổi 
	D3DXMATRIX oldMatrix;
	this->D3Dsprite->GetTransform(&oldMatrix);
	D3DXMatrixTransformation2D(
		&matrix, //Matrix
		&CenterMatrix,	//Vị trí scale
		0,		//Góc scale
		&scale, //Vector scale
		&CenterMatrix, //Vị trí góc quay
		rad,		//Góc quay theo rad
		&transform);//vector tịnh tiến = velocity
	//Vẽ theo thông số cho trước

	this->D3Dsprite->SetTransform(&matrix);
	//Vẽ
	this->D3Dsprite->Draw(texture, &source, &D3DXVECTOR3(center.x, center.y, 0), &D3DXVECTOR3(position.x, position.y, 0), color);
	//Thiết lập lại Ma trận cũ
	this->D3Dsprite->SetTransform(&oldMatrix);
}

//vẽ text
void Graphic::DrawString(char* text, RECT r, D3DCOLOR color)
{
	this->mFont->DrawTextA(this->D3Dsprite,
		text,
		-1,
		&r,
		DT_LEFT | DT_TOP,
		color);
}

//Vẽ các surface
void Graphic::DrawSurface()
{
	//Lấy Backbuffer
	this->D3Ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &Backbuffer);
}

//Lấy thiết bị vẽ
LPDIRECT3DDEVICE9 Graphic::GetDevice()
{
	return this->D3Ddev;
}
//Lấy Hwnd
HWND Graphic::GetHwnd()
{
	return this->HwndS;
}
//Lấy Sprite
LPD3DXSPRITE Graphic::GetSprite()
{
	return this->D3Dsprite;
}