#pragma once

// 트리 구조 무너뜨리지 않고 삭제 방법
// 자식의 오른쪽에 제일 작은 값이 들어가야함
// 형제의 자식들 중 가장 큰값을 넣어도 됨

class cNode {
public:
	cNode() {}
	cNode(int n);
	~cNode() { g_setPool.erase(this); }

	int nData;
	cNode* pLChild;
	cNode* pRChild;

	void Insert(int n);
	void Print();
	bool Search(int n);
	cNode* Delete(int n, cNode** ppThis);
	cNode* GetMinNode();
};
