#include <iostream>

using namespace std;

// 함수
/*
	특정 기능을 가지고 있는 구문

	절차지향
*/

// 함수의 전방선언
void PrintNumber(int num);
void Sum(int a, int b);
// *오버 로딩* -> 함수명은 동일지만 인자값을 다르게 하여 쓰는 방법
// 면접에서 물어 보는 내용
// *오버 라이드* ->  @Override 상속할때 재정의하는거
void Sum(int a);

int Mul(int a);

// 이런 경우 전방선언에만 값을 넣기를 추천함
void swap(int x, int y = 10);
void swap();

void main() {
	// 메인 함수 안에 있는 녀석만 실행 가능
	// 메인 함수에서부터 실행 가능

	PrintNumber(10);
	Sum(10, 20);

	int num = 10;
	Sum(num);
	cout << "num 은 " << num << endl;
	num = Mul(num);
	cout << "num 은 " << num << endl;

	swap(10);
	swap(20, 30);
	swap();

} // 메인 함수

// 반환값 함수명 (인자값)
void PrintNumber(int num) {
	cout << num << " 입력" << endl;
}

void Sum(int a, int b) {
	cout << a << " 더하기 " << b << " 는 " << a + b << " 입니다" << endl;
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
	cout << "swap() 함수 호출" << endl;
}

/// swap 도 함수 이미 있음 iostream 에서 제공되는지 확인은 해보자
/// 왜 void 인지 알아보는것도 좋을듯 -> 존재하지 않는다는 뜻, '공허'라고 표현함