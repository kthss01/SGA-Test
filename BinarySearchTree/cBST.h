#pragma once
class cBST
{
private:
	cNode * pRoot;
public:
	cBST();
	~cBST();

	void Insert(int n);
	void Delete(int n);
	bool Find(int n);
	void Print();
};

