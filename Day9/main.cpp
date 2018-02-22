#include <iostream>
#include <time.h>
#include <Windows.h>

using namespace std;

void ShowCard(int shape, int number);

void main() {
	srand(time(NULL));

	int card[52];			// 카드 52장
	int money = 10000;		// 소지금
	int betting;			// 배팅금액
	int turn = 0;			// 시작시 보여줄 카드용 변수
	int comNum;				// 내가 맞춰야할 뒤집혀 있는 카드 숫자
	int again;				// 게임을 다시 시작할지 확인할 변수
	int gameCount = 0;

	// 카드 초기화
	for (int i = 0; i < 52; i++)
		card[i] = i;

	// 카드 셔플
	for (int i = 0; i < 1000; i++) {
		int dest = rand() % 52;
		int sour = rand() % 52;
		
		int temp = card[dest];
		card[dest] = card[sour];
		card[sour] = temp;
	}

	// 게임 만들기
	while (true) {
		system("cls");

		// 카드 보여 주기
		for (int i = turn; i < turn + 3; i++) {
			int shape = card[i] / 13;
			int number = card[i] % 13;
			ShowCard(shape, number);
		}

		cout << "치트 : ";
		int shape = card[turn + 3] / 13;
		int number = card[turn + 3] % 13;
		ShowCard(shape, number);

		cout << "소지금 : " << money << endl;
		cout << "배팅액 (100 ~ 1000) : ";
		cin >> betting;

		// 예외 처리
		if (betting < 100 || betting > 1000) {
			cout << "다시 배팅" << endl;
			continue;
		}
		else if (money < 100) {
			cout << "파산" << endl;
			break;
		}

		// 종료(0) 하이(1) 로우(2) 세븐(3) 선택
		// 내가 맞춰야 할 카드 turn + 3
		comNum = card[turn + 3] % 13 + 1;	// 1 ~ 13
		int selectNum;
		cout << "종료(0), 하이(1), 로우(2), 세븐(3) 입력 : ";
		cin >> selectNum;

		if (selectNum == 0) {
			cout << "게임 종료 " << endl;
			break;
		}

		switch (selectNum) {
		case 1:	// 하이
			if (comNum > 7) {
				money += betting;
				cout << betting << " 획득" << endl;
				Sleep(1000);
			}
			else {
				money -= betting;
				cout << betting << " 잃음" << endl;
				Sleep(1000);
			}
			break;
		case 2: // 로우
			if (comNum < 7) {
				money += betting;
				cout << betting << " 획득" << endl;
				Sleep(1000);
			}
			else {
				money -= betting;
				cout << betting << " 잃음" << endl;
				Sleep(1000);
			}
			break;
		case 3:
			if (comNum == 7) {
				money += betting * 13;
				cout << betting << " 획득" << endl;
				Sleep(1000);
			}
			else {
				money -= betting * 13;
				cout << betting << " 잃음" << endl;
				Sleep(1000);
			}
			break;
		default:
			cout << "잘못 입력 " << endl;
			continue;
		}

		turn += 4;
		gameCount++;

		// 카드 모두 소진 시
		if (gameCount == 13) {
			// 카드 다시 셔플
			for (int i = 0; i < 1000; i++) {
				int dest = rand() % 52;
				int sour = rand() % 52;

				int temp = card[dest];
				card[dest] = card[sour];
				card[sour] = temp;
			}
			
			turn = 0;
			gameCount = 0;
		}
	}
}

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