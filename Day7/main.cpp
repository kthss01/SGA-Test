#include <iostream>

using namespace std;

void main() {
	// 문자열 뒤집기
	char str[20] = "abcdefgh";

	int len = strlen(str);
	cout << str << endl;
	cout << len << endl;
	for (int i = len - 1; i >= 0; i--) {
		cout << str[i];
	}
	cout << endl;
	


}