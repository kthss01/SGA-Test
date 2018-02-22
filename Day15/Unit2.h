#pragma once

#include <iostream>
using namespace std;

// 클래스는 클래스끼리 상속 구조체는 구조체끼리 상속

class Unit2
{
protected:
	int m_atk;
	int m_def;
public:
	Unit2();
	~Unit2();

	int GetAtk() { return m_atk; }
	void SetAtk(int atk) { m_atk = atk; }

	int GetDef() { return m_def; }
	void SetDef(int def) { m_def = def; }
};

