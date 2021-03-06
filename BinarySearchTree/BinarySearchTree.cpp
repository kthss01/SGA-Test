// BinarySearchTree.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
// BST 는 힙 정렬

#include "stdafx.h"

#include "cBST.h"

#include <iostream>
#include <assert.h>

// extern 해둬도 변수 선언 필요함
std::set<cNode*> g_setPool;
// 안에 데이터 사라졌는지 확인용도로 쓰는거
// ~pool 저장하는 공간이라 생각하면 됨

int main()
{
	cBST bst;
	for (int i = 0; i < 10; i++) {
		bst.Insert(rand() % 100);
	}

	bst.Print();

	if (bst.Find(41)) {
		std::cout << "41 존재" << std::endl;
	}

	if (!bst.Find(100)) {
		std::cout << "100 없음" << std::endl;
	}

	bst.Delete(0);
	bst.Delete(24);
	bst.Delete(34);
	bst.Delete(41);
	bst.Delete(58);
	bst.Delete(62);
	bst.Delete(64);
	bst.Delete(67);
	bst.Delete(69);
	bst.Delete(78);

	bst.Delete(100);
	bst.Delete(0);

	assert(g_setPool.empty() == true && "not Empty");

    return 0;
}

/*
	과제
	함수 포인터 조사
	함수 포인터 만드는법 
	함수 포인터 왜 사용해야 되는지

	ex) 어택이라는 함수 만들었는데 다형성 이용해서 쓰고 싶을때
*/
