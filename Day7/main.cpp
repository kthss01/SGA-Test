#include <iostream>

using namespace std;

void main() {
	// ���ڿ� ������
	char str[20] = "abcdefgh";

	int len = strlen(str);
	cout << str << endl;
	cout << len << endl;
	for (int i = len - 1; i >= 0; i--) {
		cout << str[i];
	}
	cout << endl;
	


}