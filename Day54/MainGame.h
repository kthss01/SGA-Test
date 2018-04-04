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
	효과음 구해서
	적이 피격당했을 때 사운드 플레이 및 게임 배경음악 넣어오기

	여러 몬스터가 죽는거 하려면 
	사운드가 여러번 나야되는데
	fmod의 한계로 버퍼이상 소리 내기 힘들고
	한번에 소리내는것도 10 몇개 밖에 안된다고함

	연습용으로 쓰는게 fmod라고 보면됨 이걸로 게임 만들기도 하지만
*/