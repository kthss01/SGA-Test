#include <iostream>

using namespace std;

// ���ȣ��� ��Ʈ���� �� ����
// ��ǻ�͸��� �ٸ��� �ڵ帶�� �ٸ� ���� ����
// ���ÿ��� ������������ �߰��� ������� ���� ����

void Function(int i) {
	cout << i << endl;
	Function(++i);
}

int main() {
	Function(0);
	return 0;
}