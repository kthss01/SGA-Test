#include <iostream>

using namespace std;

/*
	포인터란?
	주소값을 담을 수 있는 데이터 자료형

	int num;		-> num = 1000;

	변수의 크기 (sizeof())

	주소 값 : 0x12345678 (8자리 숫자)
*/

// Call by Value (값에 의한 호출)
void Swap(int x, int y) {
	int temp = x;
	x = y;
	y = temp;
}

// Call by Reference (주소값에 의한 호출)
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

	//// 포인터 선언 방법
	//int number = 100;
	//int* pNum;

	//pNum = &number;		// & reference (레퍼런스)

	//cout << number << endl;
	//cout << &number << endl;

	//cout << pNum << endl;
	//cout << *pNum << endl;

	//// 포인터의 메모리 크기
	//// 크기 모두 4byte로 같음
	//cout << sizeof(int*) << endl;
	//cout << sizeof(float*) << endl;
	//cout << sizeof(char*) << endl;
	//cout << sizeof(bool*) << endl;

	//// 1 byte : 0 ~ 255 까지 담을 수 있음

	int a = 10;
	int b = 1000;

	Swap(a, b);
	cout << a << endl;
	cout << b << endl;
	
	Swap(&a, &b);
	cout << a << endl;
	cout << b << endl;

	Add(a, &b);
	cout << b << endl;		// 리턴(반환) 대신 사용할 수 있음
	// 반환값은 하나만 쓸 수 있는데 여러개 쓰고 싶을 때 포인터 활용

	// 과제1
	// 빙고 게임 (개인) 만들어 오기
	// 5 x 5 
	/*
		[1][2][3][4][5]
		[6][7][8][9][10]
		[11][12][13][14][15]
		[16][17][18][19][20]
		[21][22][23][24][25]

		*빙고판에 숫자 보면서 하는거

		숫자 랜덤으로 섞어서 빙고판에 입력
		
		내가 숫자 입력 -> 빙고판 변화 -> 문자 x 로 바뀐다든지

		5줄 빙고면 종료
	*/

	// 과제2
	// 한줄 조사 '클래스'

	/// 스마트 포인터 어쩌구 교수님이 말씀했던거 조사 한번 해보면 좋을듯

}