#include "stdafx.h"
#include "MainGame6.h"


MainGame6::MainGame6()
{
}


MainGame6::~MainGame6()
{
}

HRESULT MainGame6::Init()		// 초기화
{
	GameNode::Init();

	//rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 100, 100);
	//
	//for (int i = 0; i < 5; i++) {
	//	rc[i] = RectMakeCenter
	//	(
	//		RND->GetInt(WINSIZEX),
	//		RND->GetInt(WINSIZEY),
	//		RND->GetFromInto(100, 300),
	//		RND->GetFromInto(100, 300)
	//	);
	//}
	//
	//prevTime = GetTickCount();

	m_player = RectMakeCenter(
		WINSIZEX / 2, WINSIZEY - 100, 30, 30);

	for (int i = 0; i < BULLETMAX; i++) {
		// 화면 밖으로 나가지 않게 설정
		m_bullet[i].x = RND->GetFromInto(10, WINSIZEX - 10);
		m_bullet[i].y = RND->GetFromInto(-600, 0);
		m_bullet[i].speed = RND->GetFromInto(3, 6);
		m_bullet[i].rc = RectMakeCenter(m_bullet[i].x, m_bullet[i].y, 10, 10);
	}
	
	m_score = 0;

	return S_OK;
}

void MainGame6::Release()		// 이미지를 사용하기 전까지는 쓸일이 거의 없음
{
	GameNode::Release();
}

void MainGame6::Update()		// 키보드나 마우스 처리, 자동적으로 해야할 꺼 처리
{
	GameNode::Update();

	//if (INPUT->GetKeyDown(VK_LEFT)) {
	//	rc.left -= 3.0f;
	//	rc.right -= 3.0f;
	//}
	//
	//if (INPUT->GetKeyUp(VK_RIGHT)) {
	//	rc.left += 3.0f;
	//	rc.right += 3.0f;
	//}
	//
	//// 특정 녀석 (방향키 같은거) 제외 문자를 확인하고 싶으면 문자 넣기
	//if (INPUT->GetKey('S')) {
	//	rc.top += 3.0f;
	//	rc.bottom += 3.0f;
	//}
	//
	//if (INPUT->GetToggleKey('W')) {
	//	rc.top -= 3.0f;
	//	rc.bottom -= 3.0f;
	//}
	//
	//// 컴퓨터 성능에 따라 안되는 사람도 있음
	//count++;
	//if (count % 1000) {
	//	rc.left += 3.0f;
	//	rc.right += 3.0f;
	//	count = 0;
	//}
	//
	//// 이렇게 사용하면 됨 알고 있음 됨
	//currentTime = GetTickCount();
	//if (currentTime - prevTime > 1000) {
	//	//rc.left += 3.0f;
	//	//rc.right += 3.0f;
	//
	//	for (int i = 0; i < 5; i++) {
	//		rc[i] = RectMakeCenter
	//		(
	//			RND->GetInt(WINSIZEX),
	//			RND->GetInt(WINSIZEY),
	//			RND->GetFromInto(100, 300),
	//			RND->GetFromInto(100, 300)
	//		);
	//	}
	//
	//	prevTime = GetTickCount();
	//
	//}

	// 플레이어 이동
	if (INPUT->GetKey(VK_LEFT) && m_player.left > 0) {
		m_player.left -= 5.0f;
		m_player.right -= 5.0f;
	}
	if (INPUT->GetKey(VK_RIGHT) && m_player.right < WINSIZEX) {
		m_player.left += 5.0f;
		m_player.right += 5.0f;
	}

	for (int i = 0; i < BULLETMAX; i++) {
		m_bullet[i].y += m_bullet[i].speed;
		m_bullet[i].rc = RectMakeCenter(m_bullet[i].x, m_bullet[i].y, 10, 10);
		// 화면 밖으로 나가게 되면
		if (m_bullet[i].rc.top > WINSIZEY) {
			m_bullet[i].y = RND->GetFromInto(-600, 0);
			m_score++;	// 이 때 피한걸로 간주
		}
		RECT temp;
		if (IntersectRect(&temp, &m_bullet[i].rc, &m_player)) {
			// 충돌 후 처리

			// 창 끄고 싶으면
			//PostQuitMessage(0);

			// 화면 멈추고 싶으면
			KillTimer(g_hWnd, 1);

			// 다시 시작하고 싶으면 
			//Init();

			// 일시정지 구현하고 싶으면
			//Sleep(2000);
			//Init();
			// 또는 Kill 하고 SetTimer 하면 됨
		}
	}
}

void MainGame6::Render(HDC hdc)	// 출력
{
	//GameNode::Render(hdc);
	// 백버퍼에 뿌려준다 (랜더에서 그냥 둘것)
	HDC memDC = this->GetBackBuffer()->GetMemDC();
	// 흰색 빈 비트맵
	// PatBlt 랜더링 시켜주는 함수
	// 안에 들어간 녀석 흰색으로 채우는거
	PatBlt(memDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==================================================================

	
	//Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
	//for (int i = 0; i < 5; i++) {
	//	Rectangle(hdc, rc[i].left, rc[i].top, rc[i].right, rc[i].bottom);
	//}

	int r = RND->GetInt(256);
	int g = RND->GetInt(256);
	int b = RND->GetInt(256);

	HBRUSH brush = CreateSolidBrush(RGB(r, g, b));
	FillRect(memDC, &m_player, brush);
	// render 돌때마다 brush 생성하기 때문에
	DeleteObject(brush);

	for (int i = 0; i < BULLETMAX; i++) {
		HBRUSH brush = CreateSolidBrush(RGB(r, g, b));
		// 외곽선이 없음
		// 외곽선이 필요하면 Rectangle하고
		FillRect(memDC, &m_bullet[i].rc, brush);
		// render 돌때마다 brush 생성하기 때문에
		DeleteObject(brush);
	}

	// 선생님 strScore 에러 난거 Debug x64 버젼이어서 그런거 
	// 이것만 x86로 바꿔도 에러 해결됨
	char strScore[64];
	sprintf_s(strScore, "Score : %d ", m_score);
	TextOut(memDC, 10, 10, strScore, strlen(strScore));

	//============================================================
	// 여기도 앞으로 지우면 안됨
	this->GetBackBuffer()->Render(hdc);
}

