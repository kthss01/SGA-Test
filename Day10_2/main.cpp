#include <iostream>

using namespace std;

void main() {
	int* pInt;	// ������ : �ּҰ��� ��� �ڷ��� ������
	int number = 10;

	// & (reference) -> �ּҰ��� ��Ÿ���ִ� �༮
	cout << &number << endl;
	pInt = &number;
	cout << pInt << endl;

	cout << number << endl;
	cout << *pInt << endl;

	char* str = "character pointer";	// Ư���ϰ� ���ڿ��� �ʱ�ȭ ���� 

	// ��� ��ǻ�Ϳ����� char* str�� ���� �ȵ�
	// -> const�� ���̴��� char* casting �ؾ� �Ǿ���

	char str2[64] = "character array";

	cout << str << endl;				// �ּҰ��� �ƴ� ���ڿ��� ����
	cout << str[1] << endl;
	cout << str2 << endl;

	int number2[2];

	cout << &number2[0] << endl;
	cout << &number2[1] << endl;		// 0�� �迭���� 4byte �ڿ� ����
	cout << number2 << endl;			// �迭�̸� ���� �ּ�

	// const ���
	// ���� ������ �ʵ��� ������ �ִ°�

	// const int num = 10;		// ���� �������� �ʰڴ�
	// int const num = 10;		// �ּҰ��� �������� �ʰڴ�
	// int Add (const int a);	// ���� ���ڰ��� �������� �ʰڴ�	* �� ��찡 ����
	// int Add (int a) const;	// ��ȯ���� �������� �ʰڴ�.
}