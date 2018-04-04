#include <iostream>

using namespace std;

// 재귀호출로 터트려볼 수 잇음
// 컴퓨터마다 다르고 코드마다 다를 수도 있음
// 스택영역 가득차기전에 중간에 끊어버릴 수도 있음

void Function(int i) {
	cout << i << endl;
	Function(++i);
}

int main() {
	Function(0);
	return 0;
}