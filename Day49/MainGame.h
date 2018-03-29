#pragma once

#include "GameNode.h"
#include "Rocket.h"
#include "EnemyManager.h"

// 원래대로 하려면 플레이가 되는 씬이 필요하고 거기다 enemy랑 player 넣는거

class MainGame : public GameNode
{
private:
	bool isDebug;
	EnemyManager * _em;
	Rocket* _rocket;
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

/*
	과제

	충돌 
		-> 내가 쏘면 적이 사라짐 총알도 사라지고
		-> 적이 쏘면 적의 총알 사라지고
			체력바 깍기게
	내 로켓 위에 체력바

	로켓의 그림자 만들기

*/

/*
	과제
	1. 일반 몹(Minion)을 전부 삭제 시키면 보스 등장
	//2. 일반 몬스터 출연 및 정렬 (갤러그 식으로)
	2번은 안할꺼
	등장하는 건 만들고 싶은 방법으로 만들기
	3. 보스 몬스터를 만들어서 패턴 적용
	4. 로딩 씬 -> 프로그래스 바 이용

	gameOver 씬 및 엔딩 씬 만들기
*/