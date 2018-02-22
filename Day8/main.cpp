#include <iostream>
#include <time.h>
#include <Windows.h>

using namespace std;

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

void main() {
	srand(time(NULL));

	int card[52];			// ī�� �� 52��
	int shape[3];			// ȭ�鿡 ������ ī�� 3���� ���
	int number[3];			// ȭ�鿡 ������ ī�� 3���� ����

	int dest, sour, temp;	// ���ÿ� ����

	int betting;			// ���ÿ� ����(�Է¿�)
	int money = 10000;		// ������
	int turn = 0;			// ����� ī�带 ������ ����, ���߿� 3�� �߰�
	int gameCount = 0;		// ���� ī��Ʈ

	// ī�� �ʱ�ȭ
	for (int i = 0; i < 52; i++) {
		card[i] = i;		// 0 ~ 51;
	}

	// ����
	for (int i = 0; i < 1000; i++) {
		dest = rand() % 52;
		sour = rand() % 52;

		temp = card[dest];
		card[dest] = card[sour];
		card[sour] = temp;
	}

	// ���� �����
	while (true) {
		for (int i = 0; i < 3; i++) {
			shape[i] = card[i + turn] / 13; // ���� 0 ~ 3����
			number[i] = card[i + turn] % 13; // ���� 0 ~ 12����

			// ����°�� ���� ���� ���� ���
			if (i == 2)
				//continue; // �Ǵ� break;
				cout << "ġƮ : ";

			// ����� ���� ����
			ShowCard(shape[i], number[i]);
		}
		cout << endl;
		
		// �� �ݾ��� �����ְ� ���ñݾ� �Է� �ޱ�
		cout << "������ : " << money << endl;
		cout << "���� : ";
		cin >> betting;

		// �� ���� �ݾ��� 1000 �̸��̶�� ����
		if (money < 1000) {
			cout << "�Ļ�" << endl;
			Sleep(1000);	// 1�ʰ� �����̸� ��
			break;
		}

		// ���� �ݾ��� 1000�̸� �Ǵ� �����ݺ��� ���� ��� �ٽ� ����
		if (1000 > betting || betting > money) {
			cout << "�ٽ� ����" << endl;
			Sleep(1000);
			continue;
		}

		// �˻�
		// C��° ī�� -> A B ����
		// A < C < B , B < C < A

		// �׻� A(number[0]) > B(number[1]) �ǰ� 
		// �ƴ� ���� swap
		/// min, max ���ϴ°ͺ��� �׳� swap �ع����� ����� ����
		if (number[0] < number[1]) {
			int temp = number[0];
			number[0] = number[1];
			number[1] = temp;
		}
		
		if (number[1] < number[2] && number[2] < number[0]) {
			cout << "ī�� ���� : ";
			ShowCard(shape[2], number[2]);
			cout << endl;
			money += betting;
			cout << betting << " �� ȹ��" << endl;
			Sleep(1000);
		}
		else {
			cout << "ī�� ���� : ";
			ShowCard(shape[2], number[2]);
			cout << endl;
			money -= betting;
			cout << betting << " �� ����" << endl;
			Sleep(1000);
		}
		system("cls");
		turn += 3;			// ����� ī�� ������
		gameCount++;		// ���� ī��Ʈ ����
		if (gameCount == 17) {
			cout << "ī�� ��� ����" << endl;
			Sleep(1000);
			break;
		}
	}

	// ����1
	// ī�� ���� �����
	// ���� �ο� ���� (�ߺ� ī�� ����, ���� �ý���, ������)
	/*
		���� ���� ����
			1. ���� ������ ���� ��
			2. �������� ��� �������� ����

		ī�� ��� ������ �ٽ� �����Ͽ� ���� (���� ���� x)
	*/

	/* ���� ����
		���� ī�� 3�� (ī�� ī���� �϶�� 3�� �����ִ°�)
			+ ������ �ʴ� ī�� 1��

		�÷��̾� ���� �ο� ���� �� 1���� ����

		���� �ο� ���ý�
			������ �ʴ� ī�尡 
			8 ~ K - ���� , A ~ 6 - �ο� ������ ���� �ݾ׸�ŭ ȹ��, Ʋ���� ����
		���� ���ý� -> ������ �ʴ� ī�尡 7�̸� 
			���� �ݾ��� 13�� ȹ��, �ƴ� ��� �� ��ŭ ����
	*/

	/// Ȯ�� ��굵 �����ָ� ������ ����
	/*
		���� Ȯ�� : 4/52
		�ο� Ȯ�� : 24/52
		���� Ȯ�� : 24/52
	*/

	/// �ڵ� ���õ� Ȯ���� �ٰ��ؼ� �ϰ� �ϴ°� ���?
	/*
		�Ϲ��� Ȯ���� ���� ��� ����
		������ �����ϴ� ����?
		-> 
	*/

	// ���� 2
	// ������(*) ���� ���� �ؿ���
}