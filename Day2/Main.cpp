#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
//#include <  > // 설치 할 때 만들어져 있는 파일을 불러와서 사용하겠다.
using namespace std;

void main()
{
	// 변수 선언
	// 자료형 데이터 + 변수명

	// 선언 : 맨 처음 만들었을 때
	// 정의 : 안에 내용 채우거나 바꿀 때

	// 자료형 데이터
	// int (정수값) -> -100, 0, 128

	// 선언과 동시에 초기화했다.
	// 변수명을 지정 할 때 조금은 자세하게
	int maxHp = 100;
	int damage = -20;

	cout << maxHp << endl;
	cout << damage << endl;

	maxHp = 200;
	cout << maxHp << endl;
	maxHp = maxHp + damage;
	cout << maxHp + damage << endl;
	cout << maxHp << endl;

	damage = 10.99230f; // 정수형에 소수 입력시 소숫점 버림
	cout << damage << endl;

	// 자료형 float(실수) -> 소숫점이 있는 숫자
	//float maxHp = 135.2135f; // 같은 이름 사용 할 수 없음
	float fNumber = 135.2135f;

	cout << fNumber - damage << endl;

	// 자료형 bool(참, 거짓) -> true(1) false(0)
	bool isDamage = false;
	bool isAttack = true;

	// 자료형 char(문자) 1개 'a', '@', ' '
	char str = '5';
	char str2 = '6';
	cout << str << ',' << str2 << endl;
	cout << str + str2 << endl;

	// 자료형 string(문자열) "우리가 사용하는 기본 문장들???"

	string name = "캐릭터 이름 : ";

	cout << name << endl;

	cout << "자신이 좋아하는 숫자를 하나 입력 하세요 : ";
	int number;
	string itemInfo;
	// cin 값을 입력할 때 쓰는 녀석
	//cin >> number;
	//cout << "입력하신 숫자는 " << number << "입니다." << endl;
	//cin >> itemInfo;
	//cout << itemInfo << endl;

	// cin
	// 스페이스바로 구분

	// 주말 숙제 -> 조사(반복문, 조건문) 인터넷에서 찾아서 
	// 한줄 요약 (c++ 반복문, 조건문 따로) 해오기 : 메모장이나 공책에 써오기

	// rand() -> 랜덤값을 가지는 녀석 난수 생성 가능
	// 난수 발생을 더욱 랜덤하게 만들어 주는 녀석
	srand(time(NULL));
	cout << rand() % 10 << endl; // 0 ~ 9
	cout << rand() % 10 + 1 << endl; // 0+1 ~ 9+1 -> 1 ~ 10

	int random = rand() % 100;
	
	// 주말 숙제 조건문, 반복문 각각 한줄 요약 
	
}