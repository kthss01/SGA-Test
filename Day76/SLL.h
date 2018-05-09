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
	void Insert(int count, int data);
	void Delete(int data);
	void Reverse();
	void Print();
};

