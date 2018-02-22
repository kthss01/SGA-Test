#pragma once
#include <iostream>
#include <time.h>
#include <Windows.h>
#include <conio.h>

using namespace std;

// SlidePuzzle.h
// ��� ����
class SlidePuzzle
{
private:
	int number[20];			// 5x4 or 4x5
	int temp, dest, sour;
	int zero;				// ���� 0�� ���� ����
	int lastIndex;			// ������ �ε���
	int key;				// ������ �� ����� Ű
	int move;

public:
	SlidePuzzle();
	~SlidePuzzle();

	void Init();			// �ʱ�ȭ��
	void Release();			// ������ (�����͸� ����� ��)
	void Update();			// ���� ���ӵ�����
	void Render();			// ���� ��¿�

	void Cheat();
};

