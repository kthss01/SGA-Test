#pragma once

#include <iostream>
using namespace std;

// Ŭ������ Ŭ�������� ��� ����ü�� ����ü���� ���

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

