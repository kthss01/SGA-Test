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

	// ���� ���� 0~9
	int number[10];
	// ���� ������ ���� 3��
	int selectNumber[3];
	// ��Ʈ����ũ, ��
	int strike = 0, ball = 0;
	// ���� ���� ����° ������ �ϰ� �ִ���
	int gameCount = 0;
	// �������� �ʱ�ȭ
	for (int i = 0; i < 10; i++) {
		number[i] = i;
	}
	// ���� (�������ڴ� number[0] ~ number[2])
	for (int i = 0; i < 1000; i++) {
		int sour, dest, temp;
		sour = rand() % 10;
		dest = rand() % 10;

		temp = number[dest];
		number[dest] = number[sour];
		number[sour] = temp;
	}

	// ġƮ
	for (int i = 0; i < 3; i++) {
		cout << number[i] << " ";
	}
	cout << endl;

	while (gameCount < 10) {
		// ���� 3���� �Է� ����
		cout << gameCount + 1 << "��° ����" << endl;
		cout << "0 ~ 9 ������ ���� �Է�" << endl;
		for (int i = 0; i < 3; i++) {
			cout << i+1 << "��° ���� �Է� : ";
			cin >> selectNumber[i];
			cout << endl;
		}

		// ��Ʈ����ũ �� �ƿ� �Ǻ�
		// ��Ʈ����ũ -> �ڸ���, ���� ���� ��
		// �� -> �ڸ��� �ٸ��� ���� ���� ��
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

		cout << "��Ʈ����ũ : " << strike << " �� : " << ball
			<< " �ƿ� : " << 3 - strike - ball << endl;

		if (strike == 3) {
			cout << "10�� �ȿ� ������ϴ�." << endl;
			break;
		}

		strike = 0;
		ball = 0;
		cout << endl;

		gameCount++;
		if (gameCount == 10) {
			cout << "�־��� ��ȸ�� ��� ����߽��ϴ�." << endl;
		}
	}

	// ����
	// ���� ���� 
	// �Լ�
	// ���ڿ� �Լ� (���� ���� ����)
	// strstr, strcmp, strtok, strcat, strcpy, strlen

	/// �Ѵ� ���Ŀ��� ������Ʈ ������ �� ���� �ʴٰ� ��
}