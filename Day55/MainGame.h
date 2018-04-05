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
	과제
	1. 플레이하면서 격추한 에너미의 수 출력
	2. 플레이 도중 세이브 포인트 만들어서
		세이브 포인트랑 캐릭터랑 충돌 했을 때
		특정 키를 누르면 세이브가 되게 
		세이브가 되어야 되는 데이터
		케릭터 위치, 케릭터 체력, 킬 수 
	3. 게임 종료 후 게임 실행 했을 때 자동으로 세이브한 데이터 불러와서
	위치, 체력, 킬 수 로드 되게

	float 변환, int 변환은 불러오는건 안했음
*/
