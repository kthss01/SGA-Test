#pragma once
#include <iostream>

using namespace std;

/// 구조체끼리도 상속 가능 c++에서는

// 가상 함수
/*
	메모리에 가상함수 테이블이라는 공간이 생김
	virtual attack() 저장, 호출시 이 attack()이 호출 됨
*/


class Unit
{
private:
	int maxMp;
	int currentMp;

protected:
	int maxHp;
	int currentHp;
public:
	Unit();
	~Unit();

	void Move();
	virtual void Attack();	// 가상 함수	// 내용을 채워도 문제가 안됨
};

