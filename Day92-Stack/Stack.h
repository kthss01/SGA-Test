#pragma once

// FileName : Stack.h

#include "Node.h"

// 안에 있는 조건이 true면 넘어가고 false면 error 코드 출력하는 녀석
#include <assert.h>

template<typename T>
class cStack {
private:
	cNode<T>* pTop;
public:
	cStack();
	~cStack();

	void Push(T t);
	T    Pop();
	T    Top();
	bool IsEmpty();
};

template<typename T>
cStack<T>::cStack()
	:pTop(NULL)
{
}

template<typename T>
cStack<T>::~cStack()
{
	if (pTop) {
		pTop->Destroy();
	}
}

template<typename T>
void cStack<T>::Push(T t)
{
	pTop = new cNode<T>(t, pTop);
}

template<typename T>
T cStack<T>::Pop()
{
	assert(pTop != NULL && "Pop :: Stack Empty");
	T t = pTop->tData;

	cNode<T>* pTemp = pTop;
	pTop = pTop->pNext;

	if(pTemp)
		delete pTemp;

	return t;
}

template<typename T>
T cStack<T>::Top()
{
	assert(pTop != NULL && "Pop :: Stack Empty");

	return pTop->tData;
}

template<typename T>
inline bool cStack<T>::IsEmpty()
{
	return pTop == NULL;
}
