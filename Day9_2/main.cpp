#include <iostream>

using namespace std;

/*
	�����Ͷ�?
	�ּҰ��� ���� �� �ִ� ������ �ڷ���

	int num;		-> num = 1000;

	������ ũ�� (sizeof())

	�ּ� �� : 0x12345678 (8�ڸ� ����)
*/

// Call by Value (���� ���� ȣ��)
void Swap(int x, int y) {
	int temp = x;
	x = y;
	y = temp;
}

// Call by Reference (�ּҰ��� ���� ȣ��)
void Swap(int* x, int *y) {
	int temp = *x;
	*x = *y;
	*y = temp;
}

void Add(int num, int* outNum) {
	*outNum = num + 100;
}

void Add(int num, int* outNum, float* outFNum) {
	*outNum = num + 100;
	*outFNum = *outNum + num;
}

void main() {
	//cout << sizeof(int) << endl;	// 4byte
	//cout << sizeof(float) << endl;	// 4byte
	//cout << sizeof(char) << endl;	// 1byte
	//cout << sizeof(bool) << endl;	// 1byte
	//cout << sizeof(double) << endl;
	//cout << sizeof(short) << endl;

	//// ������ ���� ���
	//int number = 100;
	//int* pNum;

	//pNum = &number;		// & reference (���۷���)

	//cout << number << endl;
	//cout << &number << endl;

	//cout << pNum << endl;
	//cout << *pNum << endl;

	//// �������� �޸� ũ��
	//// ũ�� ��� 4byte�� ����
	//cout << sizeof(int*) << endl;
	//cout << sizeof(float*) << endl;
	//cout << sizeof(char*) << endl;
	//cout << sizeof(bool*) << endl;

	//// 1 byte : 0 ~ 255 ���� ���� �� ����

	int a = 10;
	int b = 1000;

	Swap(a, b);
	cout << a << endl;
	cout << b << endl;
	
	Swap(&a, &b);
	cout << a << endl;
	cout << b << endl;

	Add(a, &b);
	cout << b << endl;		// ����(��ȯ) ��� ����� �� ����
	// ��ȯ���� �ϳ��� �� �� �ִµ� ������ ���� ���� �� ������ Ȱ��

	// ����1
	// ���� ���� (����) ����� ����
	// 5 x 5 
	/*
		[1][2][3][4][5]
		[6][7][8][9][10]
		[11][12][13][14][15]
		[16][17][18][19][20]
		[21][22][23][24][25]

		*�����ǿ� ���� ���鼭 �ϴ°�

		���� �������� ��� �����ǿ� �Է�
		
		���� ���� �Է� -> ������ ��ȭ -> ���� x �� �ٲ�ٵ���

		5�� ����� ����
	*/

	// ����2
	// ���� ���� 'Ŭ����'

	/// ����Ʈ ������ ��¼�� �������� �����ߴ��� ���� �ѹ� �غ��� ������

}