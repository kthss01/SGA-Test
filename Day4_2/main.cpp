#include <iostream>
#include <time.h>
#include <Windows.h>
using namespace std;

// Up - Down Game
void main() {
	srand(time(NULL));

	int randomNumber;
	int selectNumber;

	randomNumber = rand() % 100 + 1;
	// 0 ~ 99 + 1 -> 1 ~ 100
	int GameCount = 0;
	while (GameCount < 10)
	{
		cout << GameCount + 1 << "��° �Է�" << endl;
		cout << "1 ~ 100 ������ ���ڸ� �Է� : ";
		cin >> selectNumber;

		Sleep(1000);	// 1000 (1��)�� ȭ�鸸 ��� ����
						// sleep ���� �Է°��� ȭ�鿡 ������ ���� �� �� ����
		system("cls");	// ȭ�� ������

		if (randomNumber > selectNumber) {
			cout << "Up" << endl;
		}
		else if (randomNumber < selectNumber) {
			cout << "Down" << endl;
		}
		else {
			cout << "Find " << randomNumber << endl;
			break;
		}

		GameCount++;
	}

	// �ܼ�â���� cls ��� ġ�� ȭ�� ������
	// system() �ָܼ�ɾ� �����ϴ� ��

	/// window.h ���̺귯�� �� �˾Ƶθ� ������ 
	/// �ϳ��� �����ϴ°� ���ϱ� �̰ɷ� �� �ϴµ�
}