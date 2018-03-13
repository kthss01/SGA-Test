#pragma once

#include "GameNode.h"

class MainGame19 : public GameNode
{
private:
	bool isDebug;
public:
	MainGame19();
	~MainGame19();

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};

/*
	과제
	장비창 만들어서 장비 착용 및 스텟 변화
	스텟창도 있으면 좋고
	i key 누르면 인벤토리 열리는 식도 추가
	단축키 누르면 스텟이랑 장비창도 뜨게
*/

/*
	씬간의 데이터 이동
	씬에 대한 데이터 날라가면 안됨
	씬 매니저에서 씬 변경시 릴리즈 부분 주석 처리
	Init도 문제가 되면 이것도 주석
	씬 변경 후

*/