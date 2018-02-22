#include "Monster.h"



Monster::Monster()
{
	maxHp = currentHp = 100;
}


Monster::~Monster()
{
}

void Monster::Move()
{
	cout << "Monster의 Move() 호출" << endl;
}

void Monster::Attack()
{
	cout << "Monster의 Attack() 호출" << endl;
}

void Monster::AttackPlayer()
{
}
