#pragma once

#include "GameNode.h"

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
	주말 숙제

	1. 서브 윈도우 이미지를 출력
	타일 형식으로 되어있는 이미지 (균등한 사이즈로 잘라져있는거)
	올려주신 탱크나 타일맵

	서브 윈도우에서 이미지 클릭 하고 난후
	메인 윈도우에서 클릭 했을 때 클릭했던 이미지에 출력
	
	1.이 힘들 때
	1-1. 메인 게임에서 다하기
	메인 게임에 오른쪽에 서브윈도우에 올릴 이미지 해놓고 똑같이 

	2. F5번을 누리면 미니맵
	3. 세이브 로드
*/
