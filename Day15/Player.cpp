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
	int addAtk = m_equipWeapon.attribute;	// ���� ���ݷ�
	int addDef = m_equipArmor.attribute;	// �� ����

	cout << "================== ���� =================" << endl;
	cout << "���ݷ�\t\t" << m_atk << " + " << addAtk << endl;
	cout << "����\t\t" << m_def << " + " << addDef << endl;
	cout << "================== ���� =================" << endl;
	cout << "����\t\t:" << m_equipWeapon.name << endl;
	cout << "��\t\t:" << m_equipArmor.name << endl;

}
