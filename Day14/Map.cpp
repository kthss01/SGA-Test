#include "Map.h"



Map::Map()
{
	// 맵에 추가하는 방법

	// .insert() 맵에 추가
	pair<char*, int> pt1("레이스", 150);
	m_mNumber.insert(pt1);

	char* str = "파이어뱃";
	m_mNumber.insert(make_pair(str, 100));

	str = "고스트";
	m_mNumber[str] = 50;	// 이 방식으로 초기화하는건 추천 x	
	// 자료형 확인하고 넣는게 좋음

	//str = "레이스";
	//m_mNumber.erase(str);	// 키 값으로 지움

	//// 키값으로 특정 값을 찾는다. 검색
	//// end() 끝값 null 들어있음
	//if (m_mNumber.find(str) != m_mNumber.end()) {
	//	cout << "있다" << endl;
	//}
	//else {
	//	cout << "없다" << endl;
	//}

	// 반복자를 이용해서 출력
	m_miNumber = m_mNumber.begin();
	for (m_miNumber; m_miNumber != m_mNumber.end(); ++m_miNumber) {
		cout << m_miNumber->first << "," 
			<< m_miNumber->second << endl;
	}
}


Map::~Map()
{
}
