#include <iostream>

using namespace std;

// �Լ�
/*
	Ư�� ����� ������ �ִ� ����

	��������
*/

// �Լ��� ���漱��
void PrintNumber(int num);
void Sum(int a, int b);
// *���� �ε�* -> �Լ����� �������� ���ڰ��� �ٸ��� �Ͽ� ���� ���
// �������� ���� ���� ����
// *���� ���̵�* ->  @Override ����Ҷ� �������ϴ°�
void Sum(int a);

int Mul(int a);

// �̷� ��� ���漱�𿡸� ���� �ֱ⸦ ��õ��
void swap(int x, int y = 10);
void swap();

void main() {
	// ���� �Լ� �ȿ� �ִ� �༮�� ���� ����
	// ���� �Լ��������� ���� ����

	PrintNumber(10);
	Sum(10, 20);

	int num = 10;
	Sum(num);
	cout << "num �� " << num << endl;
	num = Mul(num);
	cout << "num �� " << num << endl;

	swap(10);
	swap(20, 30);
	swap();

} // ���� �Լ�

// ��ȯ�� �Լ��� (���ڰ�)
void PrintNumber(int num) {
	cout << num << " �Է�" << endl;
}

void Sum(int a, int b) {
	cout << a << " ���ϱ� " << b << " �� " << a + b << " �Դϴ�" << endl;
}

void Sum(int a) {
	a++;
	cout << a << endl;
}

int Mul(int a) {
	// a *= 2;
	a = a * 2;

	return a;
}

void swap(int x, int y) {
	int temp;
	
	temp = x;
	x = y;
	y = temp;

	cout << "x : " << x << " y : " << y << endl;
}

void swap(void) {
	cout << "swap() �Լ� ȣ��" << endl;
}

/// swap �� �Լ� �̹� ���� iostream ���� �����Ǵ��� Ȯ���� �غ���
/// �� void ���� �˾ƺ��°͵� ������ -> �������� �ʴ´ٴ� ��, '����'��� ǥ����