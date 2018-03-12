#pragma once

#include "GameNode.h"

class MainGame18 : public GameNode
{
private:
	bool isDebug;
public:
	MainGame18();
	~MainGame18();


	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};

/*
	카페 참고자료에 프로젝트 하나 올려주실꺼
	이미지 자동으로 슬라이스 해주는 거
	direct로 되어잇어서 png, jpg 가능
	bmp의 경우
	GetArea() 부분을 픽셀 받아오는 방법으로 바꾸고 마젠타로 바꾸면 됨

	사용방법은 프로젝트 녀석 빌드해도 되고 릴리스에 잇는거 실행해도됨
	임포터패키지에 내가 자르고 싶은거 넣어두고
	익스포터패키지에 실행시 자른 이미지 들어감

	0.data 만들어지는데
	열어보면 몇장이 짤리는지
	렉트좌표들 쭉 나옴 left,top,right, bottom 순으로
	이미지 딱 맞게 잘림
	좌표 왼쪽 상단이 0,0 
	정렬이 안되서 들어가 있음 코드 보고 이해하면됨
	이미지 크기가 다르더라도 잘림 (알파값이 0이 아닐때가 조건임)
	bmp 자르고 싶으면 마젠타가 아닐 때 조건으로 해도 됨
	(다이렉트에선 0~1 사이로 표현 되므로 1,0,1 임)
*/

/*
	Change SCENE 할때
	Update()문 가장 하단 부분에 쓰는게 좋음
	Release()하기 때문에
*/

/*
	MainGame은 진입점이라고 생각하고 씬으로 활용하기 보다는
	Scene 관리를 한다고 생각
	로그인 창처럼 생각하면 좋음

	MainGame-> Scene 관리 AddScene 이런거

	LoadingScene -> resource 관리 
		-> texture, sound, video, animation 정보, model
		*score 같은건 씬 따로 만들어서 관리하면 됨

	stage 1,2,3 마을 씬

	charactor <- gameNode 상속받아서 씬처럼 쓰기도 함 (특수한 경우)
	bg <- gameNode 상속
	stage1 <- gameNode
		stage1 내부에 charcator 플레이 하는 식
	-> 한번에 여러 씬을 update 할 수 도 있음 (나중에 해볼 꺼)
*/

/*
	과제
	상점 만들어 오기
	저번 방법과 같은데 이미지 로드해서 만들기
	마우스 클릭해서 마우스 드래그해서 옮기거나 구입 가능
	일단은 인벤토리 구입 판매까지만 스테이터스 적용 부분은 빼고
*/