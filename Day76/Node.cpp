#include "Node.h"



Node::Node()
{
}


Node::Node(int data, Node * pNext)
	:data(data), pNext(pNext)
{
}

Node::~Node()
{
}

void Node::AddNode(Node * pNext)
{
	if (this->pNext == NULL) {
		this->pNext = pNext;
	}
	else {
		this->pNext->AddNode(pNext);
	}
}

void Node::AddNode(int count, Node * pNode)
{

	if (count == 0) {
		pNode->pNext = this->pNext;
		this->pNext = pNode;
	}
	else {
		if (this->pNext == NULL)
			return;
		this->pNext->AddNode(count - 1, pNode);
	}
}

void Node::Delete()
{
	if (this->pNext != NULL)
		this->pNext->Delete();
	
	delete (this);
	//(*this) = NULL; // ¾ø¾îµµ µÊ
}

void Node::Delete(int data, Node ** ppThis)
{
	if (this->data == data) {
		*ppThis = pNext;
		delete this;
	}
	else if (this->pNext) {
		this->pNext->Delete(data, &this->pNext);
	}
}

void Node::Print()
{
	if (this->pNext == NULL) {
		cout << data << endl;
	}
	else {
		cout << data << "->";
		this->pNext->Print();
	}
}

void Node::Reverse(Node* pPrev)
{
	if (pNext) {
		pNext->Reverse(this);
	}
	pNext = pPrev;
}

Node * Node::GetTail()
{
	if (pNext) {
		return pNext->GetTail();
	}

	return this;
}
