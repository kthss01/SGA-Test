#include <iostream>
#include <time.h>
#include <Windows.h>

using namespace std;

void main() {
	srand(time(NULL));

	int number[25];				// ������ ����
	int dest, sour, temp;		// ���ÿ� ����
	int inputNum;				// �Է¹��� ����
	int bingoCount = 0;			// ���� ī��Ʈ

	// ������ �ʱ�ȭ
	for (int i = 0; i < 25; i++) {
		number[i] = i;
	}

	// ����
	for (int i = 0; i < 1000; i++) {
		dest = rand() % 25;
		sour = rand() % 25;

		temp = number[dest];
		number[dest] = number[sour];
		number[sour] = temp;
	}

	// ����
	while (true) {
		system("cls");
		cout << "==========================================" << endl;
		cout << "   BINGO\t\tBINGO COUNT : " << bingoCount << endl;
		cout << "==========================================" << endl;

		// ������ �����
		for (int i = 0; i < 25; i++) {
			// ���� ���ڰ� 35
			if (number[i] == 35) {
				// ���� ���ڰ� 35�� �� # ǥ�����ش�
				cout << (char)number[i] << "\t";
			}
			else {
				cout << number[i] << "\t";
			}
			// 5�� ��½� ��ĭ�� �����ָ鼭 �ٹٲ�
			if ((i + 1) % 5 == 0) {
				// "\n" == cout << endl
				cout << "\n\n";
			}
		}

		cout << "==========================================" << endl;
		cout << "���� �Է� :";
		cin >> inputNum;

		for (int i = 0; i < 25; i++) {
			if (number[i] == inputNum) {
				number[i] = 35;
			}
		}

		bingoCount = 0;
		for (int i = 0; i < 5; i++) {
			// ����
			if (number[i * 5 + 0] == 35 &&
				number[i * 5 + 1] == 35 &&
				number[i * 5 + 2] == 35 &&
				number[i * 5 + 3] == 35 &&
				number[i * 5 + 4] == 35) {
				bingoCount++;
			}
			// ����
			if (number[0 * 5 + i] == 35 &&
				number[1 * 5 + i] == 35 &&
				number[2 * 5 + i] == 35 &&
				number[3 * 5 + i] == 35 &&
				number[4 * 5 + i] == 35) {
				bingoCount++;
			}
		}
		// ���� �밢��
		if (number[0] == 35 &&
			number[6] == 35 &&
			number[12] == 35 &&
			number[18] == 35 &&
			number[24] == 35) {
			bingoCount++;
		}
		// ������ �밢��
		if (number[4] == 35 &&
			number[8] == 35 &&
			number[12] == 35 &&
			number[16] == 35 &&
			number[20] == 35) {
			bingoCount++;
		}

		// ���� ī��Ʈ�� 5���� �� ����
		if (bingoCount >= 5) {
			cout << "==========================================" << endl;
			cout << "\t\t��������" << endl;
			cout << "==========================================" << endl;
			Sleep(1000);
			break;
		}
	}
}