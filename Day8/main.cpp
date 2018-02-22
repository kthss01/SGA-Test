#include <iostream>
#include <time.h>
#include <Windows.h>

using namespace std;

void ShowCard(int shape, int number) {
	// 모양 세팅
	switch (shape) {
	case 0:
		cout << "♠";
		break;
	case 1:
		cout << "♥";
		break;
	case 2:
		cout << "♣";
		break;
	case 3:
		cout << "◆";
		break;
	}

	// 숫자 세팅
	// ta -> spacebar 8번 누른거랑 동일
	// \t = tap을 누른 만큼 이동
	switch (number) {
	case 0:
		cout << "A \t";
		break;
	case 10:
		cout << "J \t";
		break;
	case 11:
		cout << "Q \t";
		break;
	case 12:
		cout << "K \t";
		break;
	default:
		cout << number + 1 << " \t";
		break;
	}
}

void main() {
	srand(time(NULL));

	int card[52];			// 카드 총 52장
	int shape[3];			// 화면에 보여줄 카드 3장의 모양
	int number[3];			// 화면에 보여줄 카드 3장의 숫자

	int dest, sour, temp;	// 셔플용 변수

	int betting;			// 배팅용 변수(입력용)
	int money = 10000;		// 소지금
	int turn = 0;			// 사용한 카드를 버리는 변수, 나중에 3씩 추가
	int gameCount = 0;		// 게임 카운트

	// 카드 초기화
	for (int i = 0; i < 52; i++) {
		card[i] = i;		// 0 ~ 51;
	}

	// 셔플
	for (int i = 0; i < 1000; i++) {
		dest = rand() % 52;
		sour = rand() % 52;

		temp = card[dest];
		card[dest] = card[sour];
		card[sour] = temp;
	}

	// 게임 만들기
	while (true) {
		for (int i = 0; i < 3; i++) {
			shape[i] = card[i + turn] / 13; // 문양 0 ~ 3까지
			number[i] = card[i + turn] % 13; // 숫자 0 ~ 12까지

			// 세번째를 띄우고 싶지 않은 경우
			if (i == 2)
				//continue; // 또는 break;
				cout << "치트 : ";

			// 문양과 숫자 세팅
			ShowCard(shape[i], number[i]);
		}
		cout << endl;
		
		// 총 금액을 보여주고 배팅금액 입력 받기
		cout << "소지금 : " << money << endl;
		cout << "배팅 : ";
		cin >> betting;

		// 내 보유 금액이 1000 미만이라면 종료
		if (money < 1000) {
			cout << "파산" << endl;
			Sleep(1000);	// 1초간 딜레이를 줌
			break;
		}

		// 배팅 금액이 1000미만 또는 소지금보다 많을 경우 다시 배팅
		if (1000 > betting || betting > money) {
			cout << "다시 배팅" << endl;
			Sleep(1000);
			continue;
		}

		// 검사
		// C번째 카드 -> A B 사이
		// A < C < B , B < C < A

		// 항상 A(number[0]) > B(number[1]) 되게 
		// 아닌 경우는 swap
		/// min, max 구하는것보다 그냥 swap 해버리는 방법도 있음
		if (number[0] < number[1]) {
			int temp = number[0];
			number[0] = number[1];
			number[1] = temp;
		}
		
		if (number[1] < number[2] && number[2] < number[0]) {
			cout << "카드 숫자 : ";
			ShowCard(shape[2], number[2]);
			cout << endl;
			money += betting;
			cout << betting << " 돈 획득" << endl;
			Sleep(1000);
		}
		else {
			cout << "카드 숫자 : ";
			ShowCard(shape[2], number[2]);
			cout << endl;
			money -= betting;
			cout << betting << " 돈 잃음" << endl;
			Sleep(1000);
		}
		system("cls");
		turn += 3;			// 사용한 카드 버리기
		gameCount++;		// 게임 카운트 증가
		if (gameCount == 17) {
			cout << "카드 모두 소진" << endl;
			Sleep(1000);
			break;
		}
	}

	// 과제1
	// 카드 게임 만들기
	// 하이 로우 세븐 (중복 카드 없음, 배팅 시스템, 소지금)
	/*
		게임 종료 조건
			1. 내가 끝내고 싶을 때
			2. 소지금이 모두 떨어졌을 때만

		카드 모두 소진시 다시 셔플하여 진행 (종료 조건 x)
	*/

	/* 게임 진행
		딜러 카드 3장 (카드 카운팅 하라고 3장 보여주는거)
			+ 보이지 않는 카드 1장

		플레이어 하이 로우 세븐 중 1개를 선택

		하이 로우 선택시
			보이지 않는 카드가 
			8 ~ K - 하이 , A ~ 6 - 로우 맞으면 배팅 금액만큼 획득, 틀리면 잃음
		세븐 선택시 -> 보이지 않는 카드가 7이면 
			배팅 금액의 13배 획득, 아닌 경우 그 만큼 차감
	*/

	/// 확률 계산도 보여주면 좋을꺼 같음
	/*
		세븐 확률 : 4/52
		로우 확률 : 24/52
		하이 확률 : 24/52
	*/

	/// 자동 선택도 확률에 근거해서 하게 하는건 어떨까?
	/*
		일반적 확률이 높은 경우 선택
		세븐을 선택하는 경우는?
		-> 
	*/

	// 과제 2
	// 포인터(*) 한줄 조사 해오기
}