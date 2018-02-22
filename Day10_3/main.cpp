#include <iostream>
#include "MainGame.h"

using namespace std;

void main() {
	// 클래스

	// main.cpp

	MainGame mg;
	mg.PublicFunction();
	cout << "절   취   선" << endl;

	// 과제
	// 슬라이드 퍼즐 게임 만들기
	/*
		[0][1][2]
		[3][4][5]
		[6][7][X]

		숫자 랜덤으로 섞임
		x는 고정

		[0][4][2]
		[7][1][5]
		[6][3][X]

		w 키 누르면

		[0][4][2]
		[7][1][X]
		[6][3][5]

		s a d 이거 누른대로 교체가 되야됨

		(움직이는건 w a s d)

		[0][1][2]
		[3][4][5]
		[6][7][X]

		이게 되면 게임 끝나게

		3*3 or 5*5 해도 됨

		getch() 이용하면 좀더 게임처럼 만들 수 있음
		// 엔터 제외하고 입력 받을 수 있는 함수
		조사하면 좋다
	*/
}