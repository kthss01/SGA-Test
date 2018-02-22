#pragma once

#include "MainGame3.h"
#include <map>

/*
	Map
	map<first, second>
	first -> key	("별명")
	second -> value	("실제값")

	트리 구조로 되어있음
	검색이 빠름 -> 이미지 보관, 언젠가 쓸 녀석을 관리
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

