#include "MainGame.h"
#include <iostream>

using namespace std;

MainGame::MainGame()	// 생성자
{
	cout << "생성자 호출" << endl;
}


MainGame::~MainGame()	// 소멸자
{
	cout << "소멸자 호출" << endl;
}

void MainGame::PublicFunction()
{
	cout << "PublicFunction 호출" << endl;
	m_x = 111;
	m_y = 888;
	PrivateFunction();
	ProtectedFunction();
}

void MainGame::ProtectedFunction()
{
	cout << "ProtectedFunction 호출" << endl;
	cout << m_x << endl;
	cout << m_y << endl;
}

void MainGame::PrivateFunction()
{	
	cout << "PrivateFunction 호출" << endl;
}
