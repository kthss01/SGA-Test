#pragma once

// Ʈ�� ���� ���ʶ߸��� �ʰ� ���� ���
// �ڽ��� �����ʿ� ���� ���� ���� ������
// ������ �ڽĵ� �� ���� ū���� �־ ��

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
