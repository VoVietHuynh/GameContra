#pragma once
#include <vector>
#include "Object.h"

class BinaryTree
{
protected:
	void split(); //thuc hien chia ra cac node
	bool isContain(RECT r);

public:
	BinaryTree();
	BinaryTree(RECT bound);
	BinaryTree(RECT bound, bool isVertical);

	~BinaryTree();
	void Clear();

	void insertObject(Object* object);
	void getObjectsCollideAble(std::vector<Object*>& ObjectOut, RECT boundView);

	bool isVertical = false; 
	RECT Bound;
	std::vector<Object*> mListObject; //danh sach cac phan tu co trong vung va cham (Bound)
	BinaryTree* Left;
	BinaryTree* Right;

	void LogAllObject(int level = 0);
};