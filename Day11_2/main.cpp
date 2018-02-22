#include <iostream>
#include "Some.h"

using namespace std;

// 전처리문 (매크로)
// 숫자 뿐아니라 문자 함수도 가능
// 너무 남용하면 않 좋음, 실질적 메모리로 저장 안됨 -> 디버깅 시 확인 불가
#define CARD 30

void Render(int a);

#define FUNCTION(a) Render(a)

// 나중에 프로젝트 만들때 자주 쓰게될 내용 
// api 이상부터는 무조건적으로 쓰게 될꺼
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
	cout << "Render 호출 " << a << endl;
}