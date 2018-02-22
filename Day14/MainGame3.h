#pragma once

#include <iostream>
#include <vector>	// stl vector�� ����ϱ� ���� ����

using namespace std;

/*
	����
	- �迭�� ��ü�� �� �ִ�.
	- ���� Ÿ���� �ڷ� �����̸� ���ӵ� ��ġ�� ��ġ�ȴ�.
	ex) int num[20], int* num = new int[20]
	- ũ�⸦ �����Ӱ� ���� �����ϴ�.
*/

// ��� ���� -> ������ Ŭ���� ����� �� �ִ� �༮
// ���� ���� -> ��� �������� ����� �� �ִ� �༮
// ���� ���� -> �Լ� �ȿ��� ������ ����

/*
	�ݺ��� iterator (�����Ͷ� ����� �༮)
	�ݺ��ڴ� Ư�� �����̳�(stl) �׸���� ��� ��ȸ ����
	�˰� �ִ� ����Ʈ �������̴�.

	MainGame3* mg;
	MainGame3 mg = new MainGame3;	// ���� �Ҵ�
	// ���α׷��� ���� �ϴ� ���� - ��Ÿ��
	delete mg;

	����Ʈ �����ʹ� ���� ���� ������ ����	// ���� �Ҵ��� �������� �����Ǵ� ������ �ڵ�����
*/

/// ����Ʈ �����Ϳ� ���� ���ΰ� �ʿ��ϴ�

struct tagPlayer {
	int hp;
	int mp;
	float etc;
};

class MainGame3
{
private:
	vector<int> m_vNumber;	// m = member ���Ӹ�, v = vector, ������ ����
	vector<int>::iterator m_viNumber;

	vector<tagPlayer> m_vPlayer;
public:
	MainGame3();
	~MainGame3();
};

