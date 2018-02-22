#include "Player.h"



Player::Player()
{
}


Player::~Player()
{
}

void Player::InputPlayer()
{
	m_atk = 10;
	m_def = 10;
}

void Player::ShowStatus()
{
	int addAtk = m_equipWeapon.attribute;	// 무기 공격력
	int addDef = m_equipArmor.attribute;	// 방어구 방어력

	cout << "================== 스텟 =================" << endl;
	cout << "공격력\t\t" << m_atk << " + " << addAtk << endl;
	cout << "방어력\t\t" << m_def << " + " << addDef << endl;
	cout << "================== 장착 =================" << endl;
	cout << "무기\t\t:" << m_equipWeapon.name << endl;
	cout << "방어구\t\t:" << m_equipArmor.name << endl;

}
