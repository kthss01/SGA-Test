#pragma once
#include <iostream>
#include <time.h>
#include <Windows.h>
#include <conio.h>

using namespace std;

// SlidePuzzle.h
// 헤더 선언
class SlidePuzzle
{
private:
	int number[20];			// 5x4 or 4x5
	int temp, dest, sour;
	int zero;				// 숫자 0을 담을 변수
	int lastIndex;			// 마지막 인덱스
	int key;				// 움직일 때 사용할 키
	int move;

public:
	SlidePuzzle();
	~SlidePuzzle();

	void Init();			// 초기화용
	void Release();			// 삭제용 (포인터를 사용할 때)
	void Update();			// 실제 게임돌릴용
	void Render();			// 문자 출력용

	void Cheat();
};

