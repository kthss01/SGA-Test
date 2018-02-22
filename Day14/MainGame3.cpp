#include "MainGame3.h"

// emplace back보다 위에 아이템을 추가하는 기능 , emplace - 설치하다

MainGame3::MainGame3()
{
	// 벡터 추가 방법
	// push_back();

	for (int i = 0; i < 10; i++) {
		//cout << "capacity: " << m_vNumber.capacity() << endl;
		//// 미리 공간 확보 이전 capacity / 2 만큼 증가 4 -> 6 , 6 -> 9 , 9 -> 13
		//// 메모리 낭비가 있어서 예전엔 안썼으나 요즘은 메모리가 커서 무시하고 넘어감
		//cout << "size: " << m_vNumber.size() << endl;

		m_vNumber.push_back(i + 1);
	}

	// 삭제	(맨 뒤에서부터 삭제된다.)
	m_vNumber.pop_back();

	/*
		begin() => 배열의 0번 인덱스 (첫번째 인덱스)
		end()	=> 마지막 인덱스 (백터의 마지막 값, NULL값 들어있음)
		insert(배열의 위치(인덱스), 값) => 값 추가
		insert(배열의 위치(인덱스), 갯수, 값) => 갯수만큼 값 추가
		erase(배열의 위치 삭제)
		clear() 배열 전부 삭제
	*/
	//m_vNumber.erase(m_vNumber.begin() + 3);
	//m_vNumber.insert(m_vNumber.end() - 2, 200);
	//m_vNumber.insert(m_vNumber.begin(), 3, 100);

	//cout << m_vNumber.size() << " " << m_vNumber.capacity() << endl;

	//m_vNumber.clear();

	//m_vNumber.resize(크기) 크기 재조정
	//m_vNumber.at(인덱스 번호) 인덱스 번호 번째 값 호출
	//m_vNumber.empty() 값이 들어가 있는지 확인
	//m_vNumber.capacity() 벡터가 차지 하고 있는 실제 메모리 사이즈 갯수로 나옴

	// 출력
	//for (int i = 0; i < m_vNumber.size(); i++) {
	//	cout << m_vNumber[i] << endl;
	//}

	//m_viNumber = m_vNumber.begin();
	//for (m_viNumber; m_viNumber != m_vNumber.end(); ++m_viNumber) {
	//	cout << *m_viNumber << endl;
	//}

	// c++11 이후 생성된 녀석	
	// c++ foreach 문이라고 보면 될듯, foreach문도 c++ 존재
	// 단점 i값 변경해도 반영 안됨
	for (int i : m_vNumber) {
		cout << i << endl;
	}

	for (int i = 0; i < 10; i++) {
		tagPlayer player;
		player.hp = 100;
		player.mp = 100;
		player.etc = 0.0f + i;

		m_vPlayer.push_back(player);
	}

	for (tagPlayer player : m_vPlayer) {
		cout << player.etc << "번째 플레이어의 HP : " 
			<< player.hp << " MP : " << player.mp << endl;
	}
}


MainGame3::~MainGame3()
{
}
