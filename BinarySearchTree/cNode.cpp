#include "stdafx.h"
#include "cNode.h"

cNode::cNode(int n)
	:nData(n), 
	pLChild(NULL),
	pRChild(NULL)
{
	g_setPool.insert(this);
}

void cNode::Insert(int n)
{
	if (n < nData) {
		if (pLChild) {
			pLChild->Insert(n);
		}
		else
			pLChild = new cNode(n);
	}
	else if (n > nData) {
		if (pRChild) {
			pRChild->Insert(n);
		}
		else
			pRChild = new cNode(n);
	}
}


void cNode::Print()
{
	// ���� ���� ������ ���

	if (pLChild) {
		pLChild->Print();
	}

	std::cout << nData << std::endl;

	if (pRChild) {
		pRChild->Print();
	}

	// ū ������ ����ϰ� ������ pRChild �� pLChild ���� �ٲٱ�
}

bool cNode::Search(int n)
{
	if (n < nData) {
		if (pLChild)
			return pLChild->Search(n);
		else
			return false;
	}
	else if (n > nData) {
		if(pRChild)
			return pRChild->Search(n);
		else 
			return false;
	}
	else {
		return true;
	}

	return false;
}

// ���� ����
/*
	1. �Ѵ� ������ ������ �ø� ��
	2. �����ʸ� ������ ������ �ø��� (1�� �̶� ���� ���)
	3. ���ʸ� ���� ���ʸ� �ø� ��
	4. �ϳ��� ���� ���

	�ڽİ� �θ� ������ ���� �����Ƿ� ���� ���ѹ����°� �̿�
*/

cNode * cNode::Delete(int n, cNode ** ppThis)
{
	if (n < nData) {
		// �����Ͱ� ����
		if (pLChild == NULL) return NULL;

		return pLChild->Delete(n, &pLChild);
	}
	else if (n > nData) {
		// �����Ͱ� ����
		if (pRChild == NULL) return NULL;

		return pRChild->Delete(n, &pRChild);
	}
	else {
		// �ּҰ� ���� (������ ���� �ƴϰ�)

		// �ڽ��� ���� ���
		if (pLChild == NULL && pRChild == NULL) {
			*ppThis = NULL;
			return this;
		}
		// ���� �ڽĸ� ���� ���
		else if (pLChild != NULL && pRChild == NULL) {
			*ppThis = pLChild;
			return this;
		}
		// ������ �ڽĸ� ���� ���
		else if (pLChild == NULL & pRChild != NULL) {
			*ppThis = pRChild;
			return this;
		}
		// ���� ��� �ڽ��� ���� ���
		else {
			cNode* pMinNodeAtRightSubTree = pRChild->GetMinNode();
			nData = pMinNodeAtRightSubTree->nData;

			return pRChild->Delete(nData, &pRChild);
		}
	}

	return NULL;
}

cNode * cNode::GetMinNode()
{
	if (pLChild) {
		return pLChild->GetMinNode();
	}

	return this;
}
