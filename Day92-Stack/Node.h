#pragma once

// FileName : Node.h

template <typename T>
class cNode {
public:
	// t Data
	cNode(T t, cNode* pNext = NULL);
	~cNode();
	T tData;
	cNode* pNext;

	void Destroy();

};

template<typename T>
cNode<T>::cNode(T t, cNode * pNext)
	:tData(t), pNext(pNext)
{
}

template<typename T>
cNode<T>::~cNode()
{
}

template<typename T>
void cNode<T>::Destroy()
{
	if (pNext) {
		pNext->Destroy();
	}
	delete this;
}
