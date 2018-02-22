#include <iostream>
#include <time.h>

using namespace std;

namespace myNamespace {
	int number;
	float fNumber;
}

void main() {
	srand(time(NULL));

	myNamespace::fNumber = 3.0f;

	// 랜덤 숫자 0~9
	int number[10];
	// 내가 선택한 숫자 3개
	int selectNumber[3];
	// 스트라이크, 볼
	int strike = 0, ball = 0;
	// 현재 내가 몇판째 게임을 하고 있는지
	int gameCount = 0;
	// 랜덤숫자 초기화
	for (int i = 0; i < 10; i++) {
		number[i] = i;
	}
	// 셔플 (랜덤숫자는 number[0] ~ number[2])
	for (int i = 0; i < 1000; i++) {
		int sour, dest, temp;
		sour = rand() % 10;
		dest = rand() % 10;

		temp = number[dest];
		number[dest] = number[sour];
		number[sour] = temp;
	}

	// 치트
	for (int i = 0; i < 3; i++) {
		cout << number[i] << " ";
	}
	cout << endl;

	while (gameCount < 10) {
		// 숫자 3개를 입력 받자
		cout << gameCount + 1 << "번째 게임" << endl;
		cout << "0 ~ 9 사이의 값을 입력" << endl;
		for (int i = 0; i < 3; i++) {
			cout << i+1 << "번째 숫자 입력 : ";
			cin >> selectNumber[i];
			cout << endl;
		}

		// 스트라이크 볼 아웃 판별
		// 스트라이크 -> 자리수, 숫자 같을 때
		// 볼 -> 자리수 다르고 숫자 같을 때
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (number[i] == selectNumber[j]) {
					if (i == j) {
						strike++;
					}
					else {
						ball++;
					}
				}
			}
		}

		cout << "스트라이크 : " << strike << " 볼 : " << ball
			<< " 아웃 : " << 3 - strike - ball << endl;

		if (strike == 3) {
			cout << "10번 안에 맞췄습니다." << endl;
			break;
		}

		strike = 0;
		ball = 0;
		cout << endl;

		gameCount++;
		if (gameCount == 10) {
			cout << "주어진 기회를 모두 사용했습니다." << endl;
		}
	}

	// 과제
	// 한줄 조사 
	// 함수
	// 문자열 함수 (각각 한줄 조사)
	// strstr, strcmp, strtok, strcat, strcpy, strlen

	/// 한달 이후에는 프로젝트 생성할 일 많지 않다고 함
}