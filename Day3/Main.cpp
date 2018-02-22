#include <iostream>

using namespace std;

void main()
{
	// 조건문
	/*
		1. 
		if (조건)
		{
			참
		}
		else
		{
			거짓
		}
		switch
	*/

	/*
	bool isAttack = false;
	if (isAttack) 
	{
		cout << "공격했다" << endl;
	}
	else 
	{
		cout << "공격하지 않았다" << endl;
	}
	*/

	// 조건문 많이 사용하는 게임 : 연예 시뮬레이션 게임

	// 연산자 
	// 대입 연산자 int num = 10; a = b -> a에 b를 넣는다.
	// 사칙 연산자 '+'. '-', '*', '/', '%'
	// 비교 연산자 '>', '<', '>=', '<=', '==', '!='
	// 논술 연산자 (and, or) '&&' (and) '||' (or)
	// (and)	a(참)	&& b(참)	-> 참		
	//			a(거짓) && b(참)	-> 거짓
	//			a(거짓) && b(거짓)	-> 거짓
	/*
			ex) 
				a(참) 키를 눌렸느냐?
			&&	b(참) 몬스터가 일정거리 안에 있느냐?
			-> 참 -> 결과) 몬스터 체력 감소 
	*/
	//***** back space 옆에 \ 이거 시프트 눌러주면 | 생김

	// (or)		a(참)	|| b(참)	-> 참
	//			a(참)	|| b(거짓)	-> 참
	//			a(거짓)	|| b(거짓)	-> 거짓	
	/*
			ex)
				a	포션키를 눌렀느냐
			||	b	체력이 가득차 있느냐?
			-> 결과) 포션을 먹는다.
	*/
	//***** &(reference)

	bool isAttack = false;
	int attackRange = 0;

	if (isAttack == true && attackRange < 1) 
	{
		cout << "공격 했다" << endl;
	}
	else if(isAttack == true && attackRange > 1)
	{
		cout << "공격은 했지만 사거리가 부족했다" << endl;
	}
	else
	{
		cout << "공격 버튼을 누르지 않았다" << endl;
	}

	// switch(변수)
	int random = 20;
	char str = '!';
	/*
	switch (random) 
	{
	case 0:
		cout << "random 은 0번 선택" << endl;
		break;
	case -1:
		cout << "random 은 -1번 선택" << endl;
		break;
	case 100:
		cout << "random 은 100번 선택" << endl;
		break;
	default:
		cout << "그 외의 값을 넣었다" << endl;
		break;
	}
	*/
	switch (str) 
	{
	case '!':
		cout << "!" << endl;
	case 'a':
		cout << "a" << endl;
		break;
	case 'b':
		cout << "b" << endl;
		break;
	case 'c':
		cout << "c" << endl;
		break;
	default:
		cout << "그 외의 값을 넣었다" << endl;
		break;
	}

	cout << "switch 종료 " << endl;
	// break; 조건문이나 반복문에서만 사용되며
	// 조건문이나 반복문을 종료 할 때 사용된다

	/* 
	공부 해볼 부분
	namespace, using
	-> using namespace std; 를 쓰는 이유
	표준 라이브러리가 엄청나게 많아서 클래스나 함수 이름 정할 때
	충돌이 날 수 있음 충돌 방지를 위해 std라는 이름의 네임스페이스에 
	표준 라이브러리를 포함 시킨거
	이에 따라 새로운 헤더 이름을 만들어야 되는데 .h를 제거하는 방식 택함
	<iostream> <string>
	using 
		네임스페이스::~ 쓰는게 번거로우므로 그걸 막기 위해 using 쓰는거
	enum 
	*/

}