#include <iostream>
#include <string>
#include <time.h>
using namespace std;

void main()
{
	srand(time(NULL));
	// �迭 ����
	//int arrayNumber[10];
	//
	//arrayNumber[0] = 120;
	//arrayNumber[1] = 200;
	//arrayNumber[9] = 1000;

	//cout << arrayNumber[0] << endl;
	//cout << arrayNumber[1] << endl;
	//cout << arrayNumber[9] << endl;

	//for (int i = 0; i < 10; i++) {
	//	arrayNumber[i] = i * 100;
	//}
	//for (int i = 0; i < 10; i++) {
	//	cout << arrayNumber[i] << endl;
	//}

	// ���ڿ��� �������� NULL����(\0)�� ������ �ִ�
	//char str[6] = "abcde";
	//string test = "test string info"; // string�� null���ڸ� ������ ����
	//cout << str << endl;	// char �϶���
	//cout << str[0] << endl;
	//cout << str[2] << endl;

	int randomNumber[10];
	for (int i = 0; i < 10; i++) {
		randomNumber[i] = i + 1;
	}
	// ����
	for (int i = 0; i < 1000; i++) {
		int dest, sour, temp;
		dest = rand() % 10; // 0 ~ 9 �迭�� ũ�⸸ŭ
		sour = rand() % 10; // 0 ~ 9;

		temp = randomNumber[dest];
		randomNumber[dest] = randomNumber[sour];
		randomNumber[sour] = temp;
	}
	for (int i = 0; i < 10; i++) {
		cout << randomNumber[i] << endl;
	}

	// ����
	// ���� ���� �߱� ���� �����
	// (������) �ߺ����� �ʴ� ���� 3~4�� �������� �����ϰ�
	// �÷��̾ 3���� ���ڸ� ���� (�ߺ����� �ʴ� ����)

	/*
		ex)
		0~9 
		// ���� ���� 3��
		5 2 7
		// �÷��̾��� ���� 3�� -> ��Ʈ����ũ 1 (�ڸ� ���� ������), �� 1 (����� ������ �ڸ� x), �ƿ� 0 (������ ���� ���� x)
		5 7 0 
	*/
	// ��Ʈ����ũ -> ���ڿ� ��ġ ���� ��
	// �� -> ���ڴ� �����ϰ� ��ġ�� �ٸ� ��
	// �ƿ� -> ���ڰ� ���� ��

	// 10�� �ȿ� 3 ��Ʈ����ũ �¸�
	// 10�� �ȿ� ������ ���ϸ� �й� 
	// ���̵� �ø��� 4���� �ϴ°�

	/// ���� �����ѵ�
	/// ���־�Ʃ��� �ڵ��ϼ� ����Ű �˾ƺ���
	/// tab ������ �ڵ� �ϼ�
}