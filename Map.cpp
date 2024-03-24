#include "Map.h"
#include"TinyXML\tinyxml.h"
#include "Player.h"
#include "ObjectManager.h"
#pragma warning(disable : 4996)

Map::Map()
{
	info = new InfoMap(MapXML);

	this->tileset = new TileSet(info->tileCount, info->tileColumns, info->tileWidth, info->tileHeight);
	position = D3DXVECTOR2(0, 0);

	objectTag["Wall"] = OWall::Wall;
	objectTag["Water"] = OWall::Water;


	//Chạy wallView trước
	for (int i = 0; i < info->numObjectGroups; i++)
	{
		if (info->ObjectGroups.at(i)->name == "WallView")
		for (int j = 0; j < info->ObjectGroups.at(i)->NumOnjects; j++)
		{
			MapObject* mapObject = info->ObjectGroups.at(i)->Objects.at(j);
			int x = mapObject->x;
			int y = info->height * info->tileHeight - mapObject->y - mapObject->height;
			RECT rect = { x, y + mapObject->height, x + mapObject->width , y };
			Viewport* viewport = ObjectManager::GetInstance()->GetViewPort();
			viewport->_left = rect.left < viewport->_left ? rect.left : viewport->_left;
			viewport->_right = rect.right > viewport->_right ? rect.right : viewport->_right;
			ListWallView.push_back(rect);
		}
	}

	for (int i = 0; i < info->numObjectGroups; i++)
	{
		if (info->ObjectGroups.at(i)->name == "WallView") continue;
		if (info->ObjectGroups.at(i)->name == "View") continue;
		for (int j = 0; j < info->ObjectGroups.at(i)->NumOnjects; j++)
		{
			MapObject* mapObject = info->ObjectGroups.at(i)->Objects.at(j);
			CreateObject(mapObject);
		}
	}
}

Map::~Map()
{
	delete tileset;
	delete info;
	int size = ListObject.size();
	for (size_t i = 0; i < size; i++)
	{
		Object* obj = ListObject.at(i);
		if (obj->Tag == Object::Player) continue; //Không xóa player
		delete ListObject.at(i);
		obj = NULL;
	}
}

void Map::Update(float gameTime)
{

}

Object* Map::CreateObject(MapObject* _mapobject)
{
	D3DXVECTOR2 pos;
	pos.x = _mapobject->x + _mapobject->width / 2;
	pos.y = info->height * info->tileHeight - _mapobject->y - _mapobject->height / 2;

	Object* obj;
	Object::tag tagg = Object::GetTag(_mapobject->name);
	switch (tagg)
	{
	case Object::Player:
		obj = Player::GetInstance();
		obj->SetPositionStart(pos);
		break;
	case Object::Wall:
		switch (objectTag[_mapobject->name])
		{
		case OWall::Wall:
			obj = new OWall();
			break;
		case OWall::Water:
			obj = new Water();
			break;
		default:
			return new Object();
		}
		break;
	default:
		return new Object();
	}
	obj->id = _mapobject->id;
	obj->Init(pos, objectTag[_mapobject->name], _mapobject->kind);
	obj->SetPositionStart(pos);
	obj->GetBound(_mapobject->width, _mapobject->height);

	ListObject.push_back(obj);
	return obj;
}

void Map::Render(Viewport * view)
{
	int startH, startW, endH, endW;
	RECT r = view->GetBoundViewport();
	startH = r.bottom / info->tileHeight;
	endH = r.top / info->tileHeight + 1;
	startW = r.left / info->tileWidth;
	endW = r.right / info->tileWidth + 1;

	for (int h = startH; h < endH; h++)
		for (int w = startW; w < endW; w++)
		{
			int id = info->GetData(w, h);
			if (id > 0)
			{
				D3DXVECTOR2 position(w * info->tileWidth, (h + 1) * info->tileHeight);
				tileset->Render(view, id, position);
			}
		}
}
