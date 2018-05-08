#pragma once

#include "Node.h"

class SLL
{
private:
	Node * pHead;
public:
	SLL();
	~SLL();

	void Add(int data);
	void Print();
};

