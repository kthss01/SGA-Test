#pragma once

#include <iostream>
#include <vector>	// stl vector를 사용하기 위한 선언

using namespace std;

/*
	벡터
	- 배열을 대체할 수 있다.
	- 동일 타입의 자료 집합이며 연속된 위치에 배치된다.
	ex) int num[20], int* num = new int[20]
	- 크기를 자유롭게 조절 가능하다.
*/

// 멤버 변수 -> 지정된 클래스 사용할 수 있는 녀석
// 전역 변수 -> 어느 곳에서도 사용할 수 있는 녀석
// 지역 변수 -> 함수 안에서 선언한 변수

/*
	반복자 iterator (포인터랑 비슷한 녀석)
	반복자는 특정 컨테이너(stl) 항목들을 어떻게 순회 할지
	알고 있는 스마트 포인터이다.

	MainGame3* mg;
	MainGame3 mg = new MainGame3;	// 동적 할당
	// 프로그램이 동작 하는 순간 - 런타임
	delete mg;

	스마트 포인터는 위와 같은 과정을 생략	// 동적 할당은 해주지만 삭제되는 순간은 자동으로
*/

/// 스마트 포인터에 대한 공부가 필요하다

struct tagPlayer {
	int hp;
	int mp;
	float etc;
};

class MainGame3
{
private:
	vector<int> m_vNumber;	// m = member 줄임말, v = vector, 벡터의 선언
	vector<int>::iterator m_viNumber;

	vector<tagPlayer> m_vPlayer;
public:
	MainGame3();
	~MainGame3();
};

