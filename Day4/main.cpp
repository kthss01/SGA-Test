#include <iostream>
#include <time.h>

using namespace std;

void main() {
	srand(time(NULL));

	int selectNumber;
	int comNumber;

	int winCount = 0;
	int loseCount = 0;

	for (int i = 0; i < 5; ) {
		comNumber = rand() % 3;

		cout << i << "��° ����" << endl;
		// ġƮ
		cout << "��ǻ�Ͱ� �� ���ڴ� " << comNumber << "�Դϴ�" << endl;
		cout << "0.���� , 1.���� , 2.�� �߿��� �����ϼ���" << endl;
		cin >> selectNumber;
		if (0 > selectNumber || selectNumber > 2) {
			cout << "�ٽ� �����ϼ���" << endl;
			continue;
		}

		switch (selectNumber)
		{
		case 0:		// �÷��̾� ����
			switch (comNumber) 
			{
			case 0: // ��ǻ�� ����
				cout << "����" << endl;
				break;
			case 1: // ��ǻ�� ����
				cout << "��ǻ�Ͱ� ������ �̰��" << endl;
				loseCount++;
				break;
			case 2: // ��ǻ�� ��
				cout << "�÷��̾ ������ �̰��" << endl;
				winCount++;
				break;
			}
			break;
		case 1:		// �÷��̾� ����
			switch (comNumber)
			{
			case 0: // ��ǻ�� ����
				cout << "�÷��̾ ������ �̰��" << endl;
				winCount++;
				break;
			case 1: // ��ǻ�� ����
				cout << "����" << endl;
				break;
			case 2: // ��ǻ�� ��
				cout << "��ǻ�Ͱ� ���� �̰��" << endl;
				loseCount++;
				break;
			}
			break;
		case 2:		// �÷��̾� ��
			switch (comNumber)
			{
			case 0: // ��ǻ�� ����
				cout << "��ǻ�Ͱ� ������ �̰��" << endl;
				loseCount++;
				break;
			case 1: // ��ǻ�� ����
				cout << "�÷��̾ ���� �̰��" << endl;
				winCount++;
				break;
			case 2: // ��ǻ�� ��
				cout << "����" << endl;
				break;
			}
			break;
		}
		i++;
	}
	
	cout << "�÷��̾� : " << winCount << " �¸�, " 
		<< loseCount << " �й�, " 
		<< 5 - winCount - loseCount << " ���º�" << endl;

	cout << "������� : ";
	if (winCount > loseCount) {
		cout << "�÷��̾��� �¸�" << endl;
	}
	else if (winCount < loseCount) { 
		cout << "��ǻ���� �¸�" << endl;
	}
	else // (winCount == loseCount) 
	{
		cout << "����" << endl;
	}
}