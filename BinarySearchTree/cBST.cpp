#include "stdafx.h"
#include "cBST.h"


cBST::cBST()
	:pRoot(NULL)
{
}


cBST::~cBST()
{
}

void cBST::Insert(int n)
{
	if (pRoot) {
		pRoot->Insert(n);
	}
	else {
		pRoot = new cNode(n);
	}
}

void cBST::Delete(int n)
{
	if (pRoot) {
		cNode* pNode = pRoot->Delete(n, &pRoot);

		if (pNode) {
			delete pNode;
			pNode = NULL;
		}
	}
}

bool cBST::Find(int n)
{
	if (pRoot) {
		return pRoot->Search(n);
	}
	return false;
}

void cBST::Print()
{
	if (pRoot)
		pRoot->Print();
}
