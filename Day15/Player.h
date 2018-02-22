#pragma once

#include "Unit2.h"
#include "Inventory.h"

// unit, inventory 클래스를 상속 받는다 (다중상속)

/*
	상속 쓰기 좋은 경우
	Monster

	ex)
	monster1 -> move(), attack(), takeDamage(),
				hp,mp.atk,def
	monster2 -> move(), attack(), takeDamage(),
				hp,mp.atk,def
	monster3 -> move(), attack(), takeDamage(),
				hp,mp.atk,def
	하기보다는 

	여러 몬스터 만들려면 

	Enemy -> 
		virtual move(), 
		virtual attack(), 
		virtual takeDamage(),
				hp, mp, atk, def

	Monster1 : public Enemy;
	Monster2 : public Enemy;
		move() 재정의 이런식
	Monster3 : public Enemy;
	Monster4 : public Enemy;
	Monster5 : public Enemy;
*/

class Player : public Unit2, public Inventory
{
public:
	Player();
	~Player();

	// 플레이어 초기값 설정
	void InputPlayer();
	// 플레이어 스탯 출력
	void ShowStatus();
};

