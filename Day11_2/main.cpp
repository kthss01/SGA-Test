#include <iostream>
#include "Some.h"

using namespace std;

// ��ó���� (��ũ��)
// ���� �Ӿƴ϶� ���� �Լ��� ����
// �ʹ� �����ϸ� �� ����, ������ �޸𸮷� ���� �ȵ� -> ����� �� Ȯ�� �Ұ�
#define CARD 30

void Render(int a);

#define FUNCTION(a) Render(a)

// ���߿� ������Ʈ ���鶧 ���� ���Ե� ���� 
// api �̻���ʹ� ������������ ���� �ɲ�
#define SAFE_DELETE(p){if (p) { delete(p); (p) = nullptr }}

#define PI 3.141592f

void main() {
	//int number[CARD];

	//for (int i = 0; i < CARD; i++) {
	//	number[i] = i;
	//}

	//for (int i = 0; i < CARD; i++) {
	//	cout << number[i] << endl;
	//}

	//FUNCTION(10);

	Some some;
	some.Render();
	some.SetPosX(10);
	some.SetPosY(20);
	some.Render();
}

void Render(int a) {
	cout << "Render ȣ�� " << a << endl;
}