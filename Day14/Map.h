#pragma once

#include "MainGame3.h"
#include <map>

/*
	Map
	map<first, second>
	first -> key	("����")
	second -> value	("������")

	Ʈ�� ������ �Ǿ�����
	�˻��� ���� -> �̹��� ����, ������ �� �༮�� ����
*/

class Map
{
private:
	map<char*, int> m_mNumber;
	map<char*, int>::iterator m_miNumber;
public:
	Map();
	~Map();
};

