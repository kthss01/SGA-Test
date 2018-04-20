#pragma once

#include "GameNode.h"

//#define SUBWINOPEN 1

class MainGame : public GameNode
{
private:
	bool isDebug;

public:
	MainGame();
	~MainGame();

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};

/*
	과제
	아이소에 이미지 타일 렌더 해오기
*/

/*
	목 과제
	아이소에 맵툴 처럼 하기
	금 과제
	아이소에 A Star 적용하기
*/

/*
	과제
	iso + maptool 하기
*/

/*
	주말 과제
	1번 아이소 매트릭스 aStar 적용
	2번 16방 이미지 마우스 클릭으로 이동시키기
	3번 마우스 이미지 커서 변경하기 
		함수는 따로 없고 커서 보여주는거 말지는 있음
			ShowCurser(bool)
*/
