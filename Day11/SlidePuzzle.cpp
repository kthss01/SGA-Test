#include "SlidePuzzle.h"

SlidePuzzle::SlidePuzzle()
{
}

SlidePuzzle::~SlidePuzzle()
{
}

void SlidePuzzle::Init()
{
	srand(time(NULL));
	// 숫자 초기화
	for (int i = 0; i < 20; i++) {
		number[i] = i;
	}

	for (int i = 0; i < 1000; i++) {
		dest = rand() % 20;
		sour = rand() % 20;
		temp = number[dest];
		number[dest] = number[sour];
		number[sour] = temp;
	}

	// 스왑 (한번만)
	for (int i = 0; i < 20; i++) {
		if (number[i] == 0) {
			zero = i;
			lastIndex = number[19];
			number[19] = number[i];
			number[i] = lastIndex;
		}
	}
}

void SlidePuzzle::Release()
{
}

void SlidePuzzle::Update()
{
	while (true) {
		system("cls");
		cout << "==== 숫자 슬라이딩 퍼즐 ====" << endl;
		Render();
		cout << "================================" << endl;
		cout << "왼쪽(4), 오른쪽(6), 위(8), 아래(2) 입력 : ";
		cin >> key;

		//key = getch();

		if (key == 0 || key == 2 || key == 4 || key == 6 || key == 8);
		else {
			cout << "잘 못 입력되었습니다." << endl;
			Sleep(500);
			continue;
		}

		switch (key) {
		case 0:
			Cheat();
			break;
		case 4:	// 왼쪽
			if (zero % 5 == 0) {
				cout << "왼쪽으로 못감" << endl;
				Sleep(500);
				break;
			}
			move = number[zero];
			number[zero] = number[zero - 1];
			number[zero - 1] = move;
			zero--;
			break;
		case 6:	// 오른쪽
			if ((zero + 1) % 5 == 0) {
				cout << "오른쪽으로 못감" << endl;
				Sleep(500);
				break;
			}
			move = number[zero];
			number[zero] = number[zero + 1];
			number[zero + 1] = move;
			zero++;
			break;
		case 8:	// 위쪽
			if (zero < 5) {
				cout << "위로 못감" << endl;
				Sleep(500);
				break;
			}
			move = number[zero];
			number[zero] = number[zero - 5];
			number[zero - 5] = move;
			zero -= 5;
			break;
		case 2: // 아래쪽
			if (zero >= 15 && zero <= 19) {
				cout << "아래로 못감" << endl;
				Sleep(500);
				break;
			}
			move = number[zero];
			number[zero] = number[zero + 5];
			number[zero + 5] = move;
			zero += 5;
			break;
		}
		// 클리어 조건
		int count = 0;
		for (int i = 0; i < 20; i++) {
			if (i + 1 == number[i]) {
				count++;
			}
		}
		if (count == 19) {
			cout << "승리" << endl;
			break;
		}
	} // end of While(true)
} // end of Update()

void SlidePuzzle::Render()
{
	// 5칸씩 4줄 만들기
	for (int i = 0; i < 20; i++) {
		cout << number[i] << "\t";
		if ((i + 1) % 5 == 0) {
			cout << "\n\n" << endl;
		}
	}
}

void SlidePuzzle::Cheat()
{
	// 숫자 초기화
	for (int i = 0; i < 20; i++) {
		number[i] = i + 1;
	}
	temp = number[19];
	number[19] = number[18];
	number[18] = temp;

	number[18] = 0;
	zero = 18;
}
