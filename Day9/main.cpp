#include <iostream>
#include <time.h>
#include <Windows.h>

using namespace std;

void ShowCard(int shape, int number);

void main() {
	srand(time(NULL));

	int card[52];			// ī�� 52��
	int money = 10000;		// ������
	int betting;			// ���ñݾ�
	int turn = 0;			// ���۽� ������ ī��� ����
	int comNum;				// ���� ������� ������ �ִ� ī�� ����
	int again;				// ������ �ٽ� �������� Ȯ���� ����
	int gameCount = 0;

	// ī�� �ʱ�ȭ
	for (int i = 0; i < 52; i++)
		card[i] = i;

	// ī�� ����
	for (int i = 0; i < 1000; i++) {
		int dest = rand() % 52;
		int sour = rand() % 52;
		
		int temp = card[dest];
		card[dest] = card[sour];
		card[sour] = temp;
	}

	// ���� �����
	while (true) {
		system("cls");

		// ī�� ���� �ֱ�
		for (int i = turn; i < turn + 3; i++) {
			int shape = card[i] / 13;
			int number = card[i] % 13;
			ShowCard(shape, number);
		}

		cout << "ġƮ : ";
		int shape = card[turn + 3] / 13;
		int number = card[turn + 3] % 13;
		ShowCard(shape, number);

		cout << "������ : " << money << endl;
		cout << "���þ� (100 ~ 1000) : ";
		cin >> betting;

		// ���� ó��
		if (betting < 100 || betting > 1000) {
			cout << "�ٽ� ����" << endl;
			continue;
		}
		else if (money < 100) {
			cout << "�Ļ�" << endl;
			break;
		}

		// ����(0) ����(1) �ο�(2) ����(3) ����
		// ���� ����� �� ī�� turn + 3
		comNum = card[turn + 3] % 13 + 1;	// 1 ~ 13
		int selectNum;
		cout << "����(0), ����(1), �ο�(2), ����(3) �Է� : ";
		cin >> selectNum;

		if (selectNum == 0) {
			cout << "���� ���� " << endl;
			break;
		}

		switch (selectNum) {
		case 1:	// ����
			if (comNum > 7) {
				money += betting;
				cout << betting << " ȹ��" << endl;
				Sleep(1000);
			}
			else {
				money -= betting;
				cout << betting << " ����" << endl;
				Sleep(1000);
			}
			break;
		case 2: // �ο�
			if (comNum < 7) {
				money += betting;
				cout << betting << " ȹ��" << endl;
				Sleep(1000);
			}
			else {
				money -= betting;
				cout << betting << " ����" << endl;
				Sleep(1000);
			}
			break;
		case 3:
			if (comNum == 7) {
				money += betting * 13;
				cout << betting << " ȹ��" << endl;
				Sleep(1000);
			}
			else {
				money -= betting * 13;
				cout << betting << " ����" << endl;
				Sleep(1000);
			}
			break;
		default:
			cout << "�߸� �Է� " << endl;
			continue;
		}

		turn += 4;
		gameCount++;

		// ī�� ��� ���� ��
		if (gameCount == 13) {
			// ī�� �ٽ� ����
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
	// ��� ����
	switch (shape) {
	case 0:
		cout << "��";
		break;
	case 1:
		cout << "��";
		break;
	case 2:
		cout << "��";
		break;
	case 3:
		cout << "��";
		break;
	}

	// ���� ����
	// ta -> spacebar 8�� �����Ŷ� ����
	// \t = tap�� ���� ��ŭ �̵�
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