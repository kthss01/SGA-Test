#include <iostream>

using namespace std;

void main() {
	int* pInt;	// 포인터 : 주소값을 담는 자료형 데이터
	int number = 10;

	// & (reference) -> 주소값을 나타내주는 녀석
	cout << &number << endl;
	pInt = &number;
	cout << pInt << endl;

	cout << number << endl;
	cout << *pInt << endl;

	char* str = "character pointer";	// 특이하게 문자열로 초기화 가능 

	// 몇몇 컴퓨터에서는 char* str에 대입 안됨
	// -> const를 붙이던지 char* casting 해야 되었음

	char str2[64] = "character array";

	cout << str << endl;				// 주소값이 아닌 문자열로 나옴
	cout << str[1] << endl;
	cout << str2 << endl;

	int number2[2];

	cout << &number2[0] << endl;
	cout << &number2[1] << endl;		// 0번 배열에서 4byte 뒤에 있음
	cout << number2 << endl;			// 배열이름 시작 주소

	// const 상수
	// 값이 변하지 않도록 선언해 주는거

	// const int num = 10;		// 값을 변경하지 않겠다
	// int const num = 10;		// 주소값을 변경하지 않겠다
	// int Add (const int a);	// 들어온 인자값을 변경하지 않겠다	* 이 경우가 많음
	// int Add (int a) const;	// 반환값을 변경하지 않겠다.
}