#include <iostream>
#include <time.h>
using namespace std;

void main()
{
	// 반복문
	// for, while

	/*
		for(초기값 ; 조건 ; 증감식)
		{
			반복시킬 내용
		}
	*/

	// i = i + 1; -> i += 1; -> i++;(1일 경우만)
	// i = i + 2; -> i += 2;
	// i = i - 1; -> i -= 1; -> i--;(1일 경우만)	
	int random;
	srand(time(NULL));
	/*
	for (int i = 0; i < 10; i++) 
	{
		cout << i << "번째 실행" << endl;
		random = rand() % 10;
		cout << "랜덤 숫자 : " << random << endl;
	}
	*/

	/*
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			cout << i << " * " << j << " = " << i * j << endl;
		}
		cout << endl << endl;
	}
	*/

	// while (조건) -> 조건 참일 경우만 반복
	int i = 0;
	while (i < 10)
	{
		cout << i << "번째 실행" << endl;
		i++;
	}
	// 무한 반복문
	// while(true)

	i = 0;
	
	while (true)
	{
		i++;

		if (i % 2 == 0)
		{
			continue;
			// 반복문 안에서만 사용 할 수 있다.
			// 밑으로 내려가지 앟고 반복문의 처음으로 돌아 간다.
		}

		cout << i << "번째 실행" << endl;

		if (i > 1000)
		{
			break; // switch 나 반복문을 종료하는 녀석
		}
	}
	

	 //숙제 반복문과 조건문과 rand()를
	 //이용한 가위 바위 보 게임
	 //플레이어 2명 1명은 나, 한명은 컴퓨터
	 //가위(0), 바위(1), 보(2)
	 //나는 하나 선택
	 //총 5번 플레이
	 //매 플레이마다 누가 어떻게 이겼다. 라는 문구 출력
	 //ex) 사용자가 가위로 컴퓨터를 이겼다
	 //최종적으로 이긴 횟수, 진 횟수, 비긴 횟수 출력
	 //카페에 스샷찍어서 올리기
	
	/// 팁 : ctrl 누른채 방향키면 문서 화면 조절
	///	alt 누른채 방향키 누르면 그 라인 옮길 수 있음 


}