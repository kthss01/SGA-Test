#include <iostream>
#include <time.h>
#include <Windows.h>

using namespace std;

void main() {
	srand(time(NULL));

	int number[25];				// 빙고판 숫자
	int dest, sour, temp;		// 셔플용 변수
	int inputNum;				// 입력받을 숫자
	int bingoCount = 0;			// 빙고 카운트

	// 빙고판 초기화
	for (int i = 0; i < 25; i++) {
		number[i] = i;
	}

	// 셔플
	for (int i = 0; i < 1000; i++) {
		dest = rand() % 25;
		sour = rand() % 25;

		temp = number[dest];
		number[dest] = number[sour];
		number[sour] = temp;
	}

	// 게임
	while (true) {
		system("cls");
		cout << "==========================================" << endl;
		cout << "   BINGO\t\tBINGO COUNT : " << bingoCount << endl;
		cout << "==========================================" << endl;

		// 빙고판 만들기
		for (int i = 0; i < 25; i++) {
			// 빙고 숫자가 35
			if (number[i] == 35) {
				// 빙고 숫자가 35일 때 # 표시해준다
				cout << (char)number[i] << "\t";
			}
			else {
				cout << number[i] << "\t";
			}
			// 5개 출력시 한칸씩 내려주면서 줄바꿈
			if ((i + 1) % 5 == 0) {
				// "\n" == cout << endl
				cout << "\n\n";
			}
		}

		cout << "==========================================" << endl;
		cout << "숫자 입력 :";
		cin >> inputNum;

		for (int i = 0; i < 25; i++) {
			if (number[i] == inputNum) {
				number[i] = 35;
			}
		}

		bingoCount = 0;
		for (int i = 0; i < 5; i++) {
			// 가로
			if (number[i * 5 + 0] == 35 &&
				number[i * 5 + 1] == 35 &&
				number[i * 5 + 2] == 35 &&
				number[i * 5 + 3] == 35 &&
				number[i * 5 + 4] == 35) {
				bingoCount++;
			}
			// 세로
			if (number[0 * 5 + i] == 35 &&
				number[1 * 5 + i] == 35 &&
				number[2 * 5 + i] == 35 &&
				number[3 * 5 + i] == 35 &&
				number[4 * 5 + i] == 35) {
				bingoCount++;
			}
		}
		// 왼쪽 대각선
		if (number[0] == 35 &&
			number[6] == 35 &&
			number[12] == 35 &&
			number[18] == 35 &&
			number[24] == 35) {
			bingoCount++;
		}
		// 오른쪽 대각선
		if (number[4] == 35 &&
			number[8] == 35 &&
			number[12] == 35 &&
			number[16] == 35 &&
			number[20] == 35) {
			bingoCount++;
		}

		// 빙고 카운트가 5개일 때 종료
		if (bingoCount >= 5) {
			cout << "==========================================" << endl;
			cout << "\t\t게임종료" << endl;
			cout << "==========================================" << endl;
			Sleep(1000);
			break;
		}
	}
}