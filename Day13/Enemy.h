#pragma once
/*
	순수 가상함수는
	머리(선언)는 존재하지만 몸통(정의)가 없는 함수를 말함

	몸통은 무조건 자식이 override 해야 한다.
*/

class Enemy
{
public:
	Enemy();
	~Enemy();

	virtual void AttackPlayer() = 0; // 순수 가상함수 선언 되어있지만 정의는 되어있지 않음
};

