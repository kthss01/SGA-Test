#pragma once

#include "Unit2.h"
#include "Inventory.h"

// unit, inventory Ŭ������ ��� �޴´� (���߻��)

/*
	��� ���� ���� ���
	Monster

	ex)
	monster1 -> move(), attack(), takeDamage(),
				hp,mp.atk,def
	monster2 -> move(), attack(), takeDamage(),
				hp,mp.atk,def
	monster3 -> move(), attack(), takeDamage(),
				hp,mp.atk,def
	�ϱ⺸�ٴ� 

	���� ���� ������� 

	Enemy -> 
		virtual move(), 
		virtual attack(), 
		virtual takeDamage(),
				hp, mp, atk, def

	Monster1 : public Enemy;
	Monster2 : public Enemy;
		move() ������ �̷���
	Monster3 : public Enemy;
	Monster4 : public Enemy;
	Monster5 : public Enemy;
*/

class Player : public Unit2, public Inventory
{
public:
	Player();
	~Player();

	// �÷��̾� �ʱⰪ ����
	void InputPlayer();
	// �÷��̾� ���� ���
	void ShowStatus();
};

