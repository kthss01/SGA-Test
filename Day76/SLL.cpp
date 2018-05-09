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

void SLL::Insert(int count, int data)
{
	if (pHead) {
		Node * pNewNode = new Node(data);
		pHead->AddNode(count, pNewNode);
	}
}

void SLL::Delete(int data)
{
	if (pHead) {
		pHead->Delete(data, &pHead);
	}
}

void SLL::Reverse()
{
	if (pHead) {
		Node * pTail = pHead->GetTail();
		pHead->Reverse(NULL);
		pHead = pTail;
	}
}

void SLL::Print()
{
	if (pHead != NULL)
		pHead->Print();
}
