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
	A Star 공부
	자료구조 싱글 링키드 리스트 공부
*/

/*
	과제
	탱크 게임 A Star 적용
	내 탱크 이동도 마우스 클릭으로 이동하게
	마우스 클릭 효과 준다든지 해서 
	에너미 이동도 A Star로
	캐릭터가 범위에 들어오면 총알 발사하게
*/
