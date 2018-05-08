#include "SLL.h"



SLL::SLL()
	:pHead(NULL)
{
}


SLL::~SLL()
{
	if (pHead != NULL)
		pHead->Delete();
}

void SLL::Add(int data)
{
	Node * pNewNode = new Node(data);

	if (pHead == NULL) {
		pHead = pNewNode;
	}
	else {
		pHead->AddNode(pNewNode);
	}
}

void SLL::Print()
{
	if (pHead != NULL)
		pHead->Print();
}
