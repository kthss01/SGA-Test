#include <iostream>

using namespace std;

// ������ enum

/*
	������ 0����
	�׸��� 1�� ����

	�Է��ϸ� �Է°����� 1�� ����

	�߰� �ٲٸ�
	�߰����� 1�� ����
*/

enum STATE
{
	STATE_IDLE = 10,
	STATE_LRUN,
	STATE_RRUN,
	STATE_RJUMP,
	STATE_LJUMP
};

enum BULLET {
	BULLET_LEVEL1,
	BULLET_LEVEL2,
	BULLET_LEVEL3,
	BULLET_LEVELMAX
};

/*
	������ �����
	bullet++ �ϴ½����� LEVEL ����
*/

void main()
{

	//// ���� ����ȯ
	//char str = 'a';
	//cout << str << endl;
	//cout << (int)str << endl;	
	//float fNum = 65.135f;
	//cout << fNum << endl;
	//cout << (int)fNum << endl;	// �Ҽ� ����
	//cout << (char)fNum << endl; 

	//STATE state = (STATE) 11;		// ����ȯ ���ϸ� ���� �ȵ�
	//
	////�ڵ��ϼ����� ����� enum �־��ָ� ��
	//switch (state)
	//{
	//case STATE_IDLE:
	//	cout << "������ " << endl;
	//	break;
	//case STATE_LRUN:
	//	cout << "�޶ٻ��� " << endl;
	//	break;
	//case STATE_RRUN:
	//	cout << "���ٻ��� " << endl;
	//	break;
	//case STATE_RJUMP:
	//	cout << "�������� " << endl;
	//	break;
	//case STATE_LJUMP:
	//	cout << "�������� " << endl;
	//	break;
	//default:
	//	break;
	//}

	//if (state == STATE_LRUN) {
	//	cout << "if ������ " << endl;
	//}

	/*while (true)
	{
		cout << "10 ~ 14 �Է�" << endl;
		cout << "0���� ����" << endl;

		STATE state;
		int number;
		cin >> number;
		state = (STATE)number;
		if (number == 0) {
			break;
		}

		switch (state)
		{
		case STATE_IDLE:
			cout << "������ " << endl;
			break;
		case STATE_LRUN:
			cout << "�޶ٻ��� " << endl;
			break;
		case STATE_RRUN:
			cout << "���ٻ��� " << endl;
			break;
		case STATE_RJUMP:
			cout << "�������� " << endl;
			break;
		case STATE_LJUMP:
			cout << "�������� " << endl;
			break;
		default:
			break;
		}
	}*/

	// �ƽ�Ű �ڵ� a = 97, A = 65;
	char str = 'a';

	cout << (char)(str - 32) << endl;

	char str2[10] = "abcdefg";
	char str3[20] = "";

	for (int i = 0; i < strlen(str2); i++)
		str3[i] = str2[i] - 32;

	cout << str3 << endl;
	//cout << L"��Ƽ ����Ʈ " << endl;
	// �ѱ� �� ���� Ÿ������ ������. �����ڵ�, ��Ƽ ����Ʈ (���ڸ� 2byte�� ���� �༮)
	// �����ڵ� -> ��Ƽ ����Ʈ�� ��� �ݴ�� ����� (������ ũ�� ������)
	// ũ�� �Ű� �Ƚᵵ ��

	// �⺻������ ��� ���� -> 1byte
	// ����� (����, �ѱ�) -> 2byte

	// ���� 
	/*
		������ �����
	*/
}