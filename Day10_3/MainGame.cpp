#include "MainGame.h"
#include <iostream>

using namespace std;

MainGame::MainGame()	// ������
{
	cout << "������ ȣ��" << endl;
}


MainGame::~MainGame()	// �Ҹ���
{
	cout << "�Ҹ��� ȣ��" << endl;
}

void MainGame::PublicFunction()
{
	cout << "PublicFunction ȣ��" << endl;
	m_x = 111;
	m_y = 888;
	PrivateFunction();
	ProtectedFunction();
}

void MainGame::ProtectedFunction()
{
	cout << "ProtectedFunction ȣ��" << endl;
	cout << m_x << endl;
	cout << m_y << endl;
}

void MainGame::PrivateFunction()
{	
	cout << "PrivateFunction ȣ��" << endl;
}
