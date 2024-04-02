#include "BinaryTree.h"
#pragma warning(disable : 4996)


BinaryTree::BinaryTree()
{
}
BinaryTree::BinaryTree(RECT bound)
{
	this->Bound = bound;
	this->isVertical = false;
}

BinaryTree::BinaryTree(RECT bound, bool isVertical)
{
	this->Bound = bound;
	this->isVertical = isVertical;
}

BinaryTree::~BinaryTree()
{
}

void BinaryTree::Clear()
{
	if (Left)
	{
		Left->Clear();
		delete Left;
		Left = nullptr;
	}
	if (Right)
	{
		Right->Clear();
		delete Right;
		Right = nullptr;
	}
}


bool BinaryTree::isContain(RECT r)
{
	return Collision::isCollision(r, Bound);
}

void BinaryTree::split()
{
	//chia 2 màn hình
	RECT bound;
	if (isVertical == true)
	{
		//Map dọc
		int height = (Bound.top - Bound.bottom) / 2;

		//RECT bên dưới
		bound.left = Bound.left;
		bound.right = Bound.right;
		bound.top = Bound.top - height;
		bound.bottom = Bound.bottom;
		Left = new BinaryTree(bound, isVertical);

		//RECT bên trên
		bound.left = Bound.left;
		bound.right = Bound.right;
		bound.top = Bound.top;
		bound.bottom = Bound.top - height;
		Right = new BinaryTree(bound, isVertical);

		return;
	}

	//Map ngang
	int width = (Bound.right - Bound.left) / 2;

	//RECT bên trái
	bound.left = Bound.left;
	bound.right = Bound.left + width;
	bound.top = Bound.top;
	bound.bottom = Bound.bottom;
	Left = new BinaryTree(bound);

	//RECT bên phải
	bound.left = Bound.left + width;
	bound.right = Bound.right;
	bound.top = Bound.top;
	bound.bottom = Bound.bottom;
	Right = new BinaryTree(bound);
}

void BinaryTree::insertObject(Object* object)
{
	if (Left)
	{
		if (Left->isContain(object->GetBound()))
			Left->insertObject(object);

		if (Right->isContain(object->GetBound()))
			Right->insertObject(object);

		return;
	}

	//Thêm đối tượng vào BinaryTree
	if (this->isContain(object->GetBound()))
		this->mListObject.push_back(object);


	//Nếu map dọc check xem bound height có lớn hơn WinHeight thì tiếp tục chia nhỏ
	bool isContinue = isVertical ? Bound.top - Bound.bottom > Define::WinHeight : Bound.right - Bound.left > Define::GameWidth;
	if (isContinue)
	{
		split();
		while (!mListObject.empty())//Chia nhỏ các object tới từng node con tới khi nào hết thì dừng
		{
			if (Left->isContain(mListObject.back()->GetBound()))
				Left->insertObject(mListObject.back());

			if (Right->isContain(mListObject.back()->GetBound()))
				Right->insertObject(mListObject.back());

			mListObject.pop_back();
		}
	}
}

void BinaryTree::getObjectsCollideAble(std::vector<Object*>& ObjectOut, RECT boundView)
{
	if (Left)
	{
		Left->getObjectsCollideAble(ObjectOut, boundView);
		Right->getObjectsCollideAble(ObjectOut, boundView);
		return;
	}

	for (auto object : mListObject)
	{
		if (Collision::isCollision(object->GetBound(), boundView))
		{
			if (std::find(ObjectOut.begin(), ObjectOut.end(), object) == ObjectOut.end())
			{
				ObjectOut.push_back(object);
			}
		}
	}
}



void LogSpace(int level, string log)
{
	for (int i = 0; i < level; i++)
	{
		OutputDebugString("\t");
	}
	char _text[100];
	strcpy(_text, log.c_str()); OutputDebugString(_text);
}
void LogSpace(int level, int num)
{
	for (int i = 0; i < level; i++)
	{
		OutputDebugString("\t");
	}
	char _text[100];
	itoa(num, _text, 10);
	OutputDebugString(_text);
}

void BinaryTree::LogAllObject(int level)
{
	LogSpace(level, "ListObject: ");
	if (mListObject.size() <= 0) OutputDebugString("Empty");

	for (auto object : mListObject)
	{
		OutputDebugString("   "); LogSpace(0, object->GetName()); OutputDebugString("_");
		LogSpace(0, object->positionStart.x); OutputDebugString("_"); LogSpace(0, object->positionStart.y);
	}

	if (Left)
	{
		OutputDebugString("\n");
		LogSpace(level, level); OutputDebugString("Left:\n");
		Left->LogAllObject(level + 1);

		OutputDebugString("\n");
		LogSpace(level, level); OutputDebugString("Right:\n");
		Right->LogAllObject(level + 1);
	}
	//OutputDebugString("\n");
}