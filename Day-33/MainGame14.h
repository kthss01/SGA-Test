#pragma once

#include "GameNode.h"

// 과제 풀이

#define SIZEX 117
#define SIZEY 138
#define SPEED 7
#define GRAVITY 0.5f	// 점프했을 때 중력값 받을 정도
#define JUMP -15		// 얼마 정도 점프가 되었는지

enum STATUS {
	STATUS_NORMAL,
	STATUS_ONLAND,
	STATUS_TOUP,
	STATUS_TOLOW,		// 좌표값이 밑으로 내려가는거 떨어지는 애니메이션 출력
	STATUS_LANDING,		// 말그대로 떨어지는거 일정 애니메이션만 돌릴꺼
	STATUS_WALL,
	STATUS_CLIMB		// 벽을 잡고 있다가 올라가는 상태
};

class MainGame14 : public GameNode
{
private:
	STATUS status;
	
	// moveFrame 움직이는 애니메이션 
	// 이건 frame 계산할 때 쓸거 중첩으로 더해져서 쓰게 할 꺼
	// 좀더 frame 정확하게 되게 하기 위해서 계싼을 위해 사용할 꺼 
	// (결국엔 int 형 넣긴함)
	float x = 100, y = 572 - SIZEY / 2, moveFrame = 0;
	
	float vy;

	// 0 , 1 내가 발판으로 쓰고있을 녀석, 
	// 2 젤 위에 있는 녀석, 
	// 3이 충돌햇을 때 벽 잡는 모션 있는 녀석
	RECT box[4]; 
	RECT temp; // 충돌할 때마다 쓸 녀석
	
	// vector 애니메이션 돌릴 때 쓸 녀석
	// 애니메이션 3중 벡터 쓸 거
	int vector = 1, boxNum = 0;
	
	// 캐릭터 [] 왼쪽 오른쪽이냐
	// 캐릭터 [][] 애니메이션 동작 6가지 뛰는거 걷는거 점프하는거 같은
	// 캐릭터 [][][] 해당 애니메이션의 프레임
	Image* bg, *character[2][7][11];
	

	char str[128]; // 파일 부를때 쓸거 sprintf_s 이용할 때

public:
	MainGame14();
	~MainGame14();

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void Move(); // 이동할 때 애니메이션
	void Jump(); // 점프할 때
};

/*
	atlas xml site
	이거 이용해서 
*/

/*
	디버깅 하는 방법
		빌드 실패인 경우
			오타인 경우가 많음
		메모리 초기화 안해 준 경우
			예외가 발생함 엑세스 위반 뜸 
			찾기 쉬운 상태에서 디버그 클릭 후 호출 스택 볼 수 있음
			호출 스택 어떠한 순서대로 함수 호출했는지 볼 수 있는거
			역순으로 보여줌
			추가적으로 어떤 문제인지 보려면 자동을 보면됨
		외부기호 참조 문제
			두가지 있음
				함수 정의 안햇을 때 이렇게 뜸
				함수 호출 할 수는 있는데 내용 사용할 수 없을 때 뜸
				자세히 읽어보면 찾을 수는 잇음
				
			ex) #pragma comment(lib, "msimg32.lib") 주석 처리 한 겨우
			AlphaBlend 함수에서 문제가 발생하고 구글에 검색해서 해결

		잘 동작하는거 같은데 실행 중에 에러 뜨는 경우
		무한반복 하는 경우가 많음 (초기화 같은거를)

		천개 정도 반복문 돌 때
		특정 번째에 대해서 확인하고 싶을 때
		반복문 안에 찍은 후
		디버그 안에 조사식이라고 있음 
		조사식은 임의의 값 조사하는 것
		조사식에 i를 쓰고
			i 값을 수정하고 F10 누르면 디버그 값도 수정 됨 
			i 5로하면 0~4까지 다 실행하고 나서의 값임

		중단점
			특정한 녀석에서 값을 확인하기 위한 방법
			왼쪽 끝에 누르거나 그 라인에서 F9 누름 됨
			F5누르면 그 라인에서 멈춤
			F10 누르면 한 칸 내려가고 F11 누르면 함수가 있을시 함수로 들어감

		API에서는 F5누르는걸 추천함 콘솔에서처럼 Ctrl + F5 누르지말고
		콘솔에서 F5누르면 창이 안켜져서 Ctrl + F5 누르라고 알려주신 거

		비주얼 문제도 비주얼도 디버그 할 수 있음
*/

/*
	과제
	섯다 이미지 넣어서 만들어 오기
*/