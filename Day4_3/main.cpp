#include <iostream>
#include <string>
#include <time.h>
using namespace std;

void main()
{
	srand(time(NULL));
	// 배열 선언
	//int arrayNumber[10];
	//
	//arrayNumber[0] = 120;
	//arrayNumber[1] = 200;
	//arrayNumber[9] = 1000;

	//cout << arrayNumber[0] << endl;
	//cout << arrayNumber[1] << endl;
	//cout << arrayNumber[9] << endl;

	//for (int i = 0; i < 10; i++) {
	//	arrayNumber[i] = i * 100;
	//}
	//for (int i = 0; i < 10; i++) {
	//	cout << arrayNumber[i] << endl;
	//}

	// 문자열은 마지막에 NULL문자(\0)를 가지고 있다
	//char str[6] = "abcde";
	//string test = "test string info"; // string도 null문자를 가지고 있음
	//cout << str << endl;	// char 일때만
	//cout << str[0] << endl;
	//cout << str[2] << endl;

	int randomNumber[10];
	for (int i = 0; i < 10; i++) {
		randomNumber[i] = i + 1;
	}
	// 셔플
	for (int i = 0; i < 1000; i++) {
		int dest, sour, temp;
		dest = rand() % 10; // 0 ~ 9 배열의 크기만큼
		sour = rand() % 10; // 0 ~ 9;

		temp = randomNumber[dest];
		randomNumber[dest] = randomNumber[sour];
		randomNumber[sour] = temp;
	}
	for (int i = 0; i < 10; i++) {
		cout << randomNumber[i] << endl;
	}

	// 과제
	// 게임 숫자 야구 게임 만들기
	// (상대방이) 중복되지 않는 숫자 3~4개 랜덤으로 선택하고
	// 플레이어가 3개의 숫자를 선택 (중복되지 않는 숫자)

	/*
		ex)
		0~9 
		// 랜덤 숫자 3개
		5 2 7
		// 플레이어의 선택 3개 -> 스트라이크 1 (자리 숫자 같으면), 볼 1 (존재는 하지만 자리 x), 아웃 0 (선택한 숫자 존재 x)
		5 7 0 
	*/
	// 스트라이크 -> 숫자와 위치 같을 때
	// 볼 -> 숫자는 존재하고 위치가 다를 때
	// 아웃 -> 숫자가 없을 때

	// 10번 안에 3 스트라이크 승리
	// 10번 안에 맞추지 못하면 패배 
	// 난이도 올리면 4개로 하는거

	/// 셔플 유용한듯
	/// 비주얼스튜디오 자동완성 단축키 알아보자
	/// tab 누르면 자동 완성
}