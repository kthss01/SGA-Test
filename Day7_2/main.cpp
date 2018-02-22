#include <iostream>

using namespace std;

// 열거형 enum

/*
	시작은 0부터
	그리고 1씩 증가

	입력하면 입력값부터 1씩 증가

	중간 바꾸면
	중간부터 1씩 증가
*/

enum STATE
{
	STATE_IDLE = 10,
	STATE_LRUN,
	STATE_RRUN,
	STATE_RJUMP,
	STATE_LJUMP
};

enum BULLET {
	BULLET_LEVEL1,
	BULLET_LEVEL2,
	BULLET_LEVEL3,
	BULLET_LEVELMAX
};

/*
	아이템 습득시
	bullet++ 하는식으로 LEVEL 관리
*/

void main()
{

	//// 강제 형변환
	//char str = 'a';
	//cout << str << endl;
	//cout << (int)str << endl;	
	//float fNum = 65.135f;
	//cout << fNum << endl;
	//cout << (int)fNum << endl;	// 소수 날라감
	//cout << (char)fNum << endl; 

	//STATE state = (STATE) 11;		// 형변환 안하면 대입 안됨
	//
	////자동완성으로 만들고 enum 넣어주면 됨
	//switch (state)
	//{
	//case STATE_IDLE:
	//	cout << "대기상태 " << endl;
	//	break;
	//case STATE_LRUN:
	//	cout << "왼뛰상태 " << endl;
	//	break;
	//case STATE_RRUN:
	//	cout << "오뛰상태 " << endl;
	//	break;
	//case STATE_RJUMP:
	//	cout << "왼점상태 " << endl;
	//	break;
	//case STATE_LJUMP:
	//	cout << "오점상태 " << endl;
	//	break;
	//default:
	//	break;
	//}

	//if (state == STATE_LRUN) {
	//	cout << "if 문으로 " << endl;
	//}

	/*while (true)
	{
		cout << "10 ~ 14 입력" << endl;
		cout << "0번은 종료" << endl;

		STATE state;
		int number;
		cin >> number;
		state = (STATE)number;
		if (number == 0) {
			break;
		}

		switch (state)
		{
		case STATE_IDLE:
			cout << "대기상태 " << endl;
			break;
		case STATE_LRUN:
			cout << "왼뛰상태 " << endl;
			break;
		case STATE_RRUN:
			cout << "오뛰상태 " << endl;
			break;
		case STATE_RJUMP:
			cout << "왼점상태 " << endl;
			break;
		case STATE_LJUMP:
			cout << "오점상태 " << endl;
			break;
		default:
			break;
		}
	}*/

	// 아스키 코드 a = 97, A = 65;
	char str = 'a';

	cout << (char)(str - 32) << endl;

	char str2[10] = "abcdefg";
	char str3[20] = "";

	for (int i = 0; i < strlen(str2); i++)
		str3[i] = str2[i] - 32;

	cout << str3 << endl;
	//cout << L"멀티 바이트 " << endl;
	// 한글 두 가지 타입으로 나눠짐. 유니코드, 멀티 바이트 (문자를 2byte로 쓰는 녀석)
	// 유니코드 -> 멀티 바이트는 쉬운데 반대는 어려움 (데이터 크기 때문에)
	// 크게 신경 안써도 됨

	// 기본적으로 모두 영어 -> 1byte
	// 동양권 (한자, 한글) -> 2byte

	// 과제 
	/*
		월남뽕 만들기
	*/
}