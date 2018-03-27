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
	과제1
	에너미 추가
	8 * 4 (수량)

	갤러그 처럼 이동
	지그재그 형식으로 이동

	게임 시작하면 일정 방향으로 이동하고
	끝에 방향으로 이동하면 한칸내려가고 반대 방향으로 이동
	일정위치 로 다시 올라가서

	충돌은 일단 하지말고

	과제2
	공용 총알 Bullet 채워오기
	Bullet(각도)
	32마리 에너미 캐릭터에게 발사
	유도탄 x 총알은 그 캐릭터와의 각도로 나가게
*/