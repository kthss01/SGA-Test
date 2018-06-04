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
	// 가장 작은 순으로 출력

	if (pLChild) {
		pLChild->Print();
	}

	std::cout << nData << std::endl;

	if (pRChild) {
		pRChild->Print();
	}

	// 큰 순으로 출력하고 싶으면 pRChild 랑 pLChild 순서 바꾸기
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

// 삭제 조건
/*
	1. 둘다 있으면 오른쪽 올림 됨
	2. 오른쪽만 있으면 오른쪽 올림됨 (1번 이랑 같은 경우)
	3. 왼쪽만 있음 왼쪽만 올림 됨
	4. 하나도 없는 경우

	자식과 부모 데이터 형이 같으므로 스왑 시켜버리는걸 이용
*/

cNode * cNode::Delete(int n, cNode ** ppThis)
{
	if (n < nData) {
		// 데이터가 없다
		if (pLChild == NULL) return NULL;

		return pLChild->Delete(n, &pLChild);
	}
	else if (n > nData) {
		// 데이터가 없다
		if (pRChild == NULL) return NULL;

		return pRChild->Delete(n, &pRChild);
	}
	else {
		// 주소값 대입 (데이터 스왑 아니고)

		// 자식이 없을 경우
		if (pLChild == NULL && pRChild == NULL) {
			*ppThis = NULL;
			return this;
		}
		// 왼쪽 자식만 있을 경우
		else if (pLChild != NULL && pRChild == NULL) {
			*ppThis = pLChild;
			return this;
		}
		// 오른쪽 자식만 있을 경우
		else if (pLChild == NULL & pRChild != NULL) {
			*ppThis = pRChild;
			return this;
		}
		// 양쪽 모두 자식이 있을 경우
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
