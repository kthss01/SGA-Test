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