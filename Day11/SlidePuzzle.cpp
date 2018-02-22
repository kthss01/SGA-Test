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
	// ���� �ʱ�ȭ
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

	// ���� (�ѹ���)
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
		cout << "==== ���� �����̵� ���� ====" << endl;
		Render();
		cout << "================================" << endl;
		cout << "����(4), ������(6), ��(8), �Ʒ�(2) �Է� : ";
		cin >> key;

		//key = getch();

		if (key == 0 || key == 2 || key == 4 || key == 6 || key == 8);
		else {
			cout << "�� �� �ԷµǾ����ϴ�." << endl;
			Sleep(500);
			continue;
		}

		switch (key) {
		case 0:
			Cheat();
			break;
		case 4:	// ����
			if (zero % 5 == 0) {
				cout << "�������� ����" << endl;
				Sleep(500);
				break;
			}
			move = number[zero];
			number[zero] = number[zero - 1];
			number[zero - 1] = move;
			zero--;
			break;
		case 6:	// ������
			if ((zero + 1) % 5 == 0) {
				cout << "���������� ����" << endl;
				Sleep(500);
				break;
			}
			move = number[zero];
			number[zero] = number[zero + 1];
			number[zero + 1] = move;
			zero++;
			break;
		case 8:	// ����
			if (zero < 5) {
				cout << "���� ����" << endl;
				Sleep(500);
				break;
			}
			move = number[zero];
			number[zero] = number[zero - 5];
			number[zero - 5] = move;
			zero -= 5;
			break;
		case 2: // �Ʒ���
			if (zero >= 15 && zero <= 19) {
				cout << "�Ʒ��� ����" << endl;
				Sleep(500);
				break;
			}
			move = number[zero];
			number[zero] = number[zero + 5];
			number[zero + 5] = move;
			zero += 5;
			break;
		}
		// Ŭ���� ����
		int count = 0;
		for (int i = 0; i < 20; i++) {
			if (i + 1 == number[i]) {
				count++;
			}
		}
		if (count == 19) {
			cout << "�¸�" << endl;
			break;
		}
	} // end of While(true)
} // end of Update()

void SlidePuzzle::Render()
{
	// 5ĭ�� 4�� �����
	for (int i = 0; i < 20; i++) {
		cout << number[i] << "\t";
		if ((i + 1) % 5 == 0) {
			cout << "\n\n" << endl;
		}
	}
}

void SlidePuzzle::Cheat()
{
	// ���� �ʱ�ȭ
	for (int i = 0; i < 20; i++) {
		number[i] = i + 1;
	}
	temp = number[19];
	number[19] = number[18];
	number[18] = temp;

	number[18] = 0;
	zero = 18;
}
