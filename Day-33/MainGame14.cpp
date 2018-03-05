#include "stdafx.h"
#include "MainGame14.h"


MainGame14::MainGame14()
{
}


MainGame14::~MainGame14()
{
}

HRESULT MainGame14::Init()
{
	GameNode::Init();

	bg = new Image;
	bg->Init("images/메가맨배경.bmp", WINSIZEX, WINSIZEY);

	// 이런식으로 설정시 문제가 될 수 있음
	// 화면 창 크기가 변화가 되었을 때 문제가 발생함
	// 문제가 없도록 하려면 기준점으로 짜야하긴함 
	box[0] = { 0, 572, WINSIZEX, WINSIZEY };
	box[1] = { 704, 486, 1025, 510 };
	box[2] = { 1026, 223, WINSIZEX, 223 };
	box[3] = { 960, 190, 1026, 260 };

	for (int i = 0; i < 11; i++) {
		character[0][STATUS_ONLAND][i] = new Image;
		sprintf_s(str, "images/왼쪽걷기%d.bmp", i + 1);
		character[0][STATUS_ONLAND][i]->Init(str, SIZEX, SIZEY,
			true, RGB(255, 0, 255));
		character[1][STATUS_ONLAND][i] = new Image;
		sprintf_s(str, "images/오른쪽걷기%d.bmp", i + 1);
		character[1][STATUS_ONLAND][i]->Init(str, SIZEX, SIZEY,
			true, RGB(255, 0, 255));
	}

	for (int i = 0; i < 6; i++) {
		character[0][STATUS_NORMAL][i] = new Image;
		sprintf_s(str, "images/왼쪽평시%d.bmp", i + 1);
		character[0][STATUS_NORMAL][i]->Init(str, SIZEX, SIZEY,
			true, RGB(255, 0, 255));
		character[1][STATUS_NORMAL][i] = new Image;
		sprintf_s(str, "images/오른쪽평시%d.bmp", i + 1);
		character[1][STATUS_NORMAL][i]->Init(str, SIZEX, SIZEY,
			true, RGB(255, 0, 255));
	}

	for (int i = 0; i < 5; i++) {
		character[0][STATUS_TOUP][i] = new Image;
		sprintf_s(str, "images/왼쪽점프%d.bmp", i + 1);
		character[0][STATUS_TOUP][i]->Init(str, SIZEX, SIZEY,
			true, RGB(255, 0, 255));
		character[1][STATUS_TOUP][i] = new Image;
		sprintf_s(str, "images/오른쪽점프%d.bmp", i + 1);
		character[1][STATUS_TOUP][i]->Init(str, SIZEX, SIZEY,
			true, RGB(255, 0, 255));

		character[0][STATUS_TOLOW][i] = new Image;
		sprintf_s(str, "images/왼쪽점프%d.bmp", i + 6);
		character[0][STATUS_TOLOW][i]->Init(str, SIZEX, SIZEY,
			true, RGB(255, 0, 255));
		character[1][STATUS_TOLOW][i] = new Image;
		sprintf_s(str, "images/오른쪽점프%d.bmp", i + 6);
		character[1][STATUS_TOLOW][i]->Init(str, SIZEX, SIZEY,
			true, RGB(255, 0, 255));
	}

	// 점프 11 12 는 착지 모션
	character[0][STATUS_LANDING][0] = new Image;
	character[0][STATUS_LANDING][0]->Init("images/왼쪽점프11.bmp",
		SIZEX, SIZEY, true, RGB(255, 0, 255));
	character[0][STATUS_LANDING][1] = new Image;
	character[0][STATUS_LANDING][1]->Init("images/왼쪽점프12.bmp",
		SIZEX, SIZEY, true, RGB(255, 0, 255));

	character[1][STATUS_LANDING][0] = new Image;
	character[1][STATUS_LANDING][0]->Init("images/오른쪽점프11.bmp",
		SIZEX, SIZEY, true, RGB(255, 0, 255));
	character[1][STATUS_LANDING][1] = new Image;
	character[1][STATUS_LANDING][1]->Init("images/오른쪽점프12.bmp",
		SIZEX, SIZEY, true, RGB(255, 0, 255));

	// 1 벽에 매달리는 모션 2,3 은 올라가는 모션
	character[0][STATUS_WALL][0] = new Image;
	character[0][STATUS_WALL][0]->Init("images/왼쪽벽잡기1.bmp",
		SIZEX, SIZEY, true, RGB(255, 0, 255));

	character[0][STATUS_CLIMB][0] = new Image;
	character[0][STATUS_CLIMB][0]->Init("images/왼쪽벽잡기2.bmp",
		SIZEX, SIZEY, true, RGB(255, 0, 255));
	character[0][STATUS_CLIMB][1] = new Image;
	character[0][STATUS_CLIMB][1]->Init("images/왼쪽벽잡기3.bmp",
		SIZEX, SIZEY, true, RGB(255, 0, 255));

	character[1][STATUS_WALL][0] = new Image;
	character[1][STATUS_WALL][0]->Init("images/오른쪽벽잡기1.bmp",
		SIZEX, SIZEY, true, RGB(255, 0, 255));

	character[1][STATUS_CLIMB][0] = new Image;
	character[1][STATUS_CLIMB][0]->Init("images/오른쪽벽잡기2.bmp",
		SIZEX, SIZEY, true, RGB(255, 0, 255));
	character[1][STATUS_CLIMB][1] = new Image;
	character[1][STATUS_CLIMB][1]->Init("images/오른쪽벽잡기3.bmp",
		SIZEX, SIZEY, true, RGB(255, 0, 255));

	status = STATUS_NORMAL;

	return S_OK;
}

void MainGame14::Release()
{
	GameNode::Release();

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 6; j++) {
			for (int k = 0; k < 11; k++) {
				// 존재하면 지우겠다는거 들어가 있는게 다 다르니
				if (character[i][j][k])
					SAFE_DELETE(character[i][j][k]);
			}
		}
	}
	SAFE_DELETE(bg);
}

void MainGame14::Update()
{
	GameNode::Update();

	// 현재 애니메이션 클립당 어떠한 동작을 취할지 진행 할 꺼
	// Move() Jump()에선 실제 어떻게 바뀔지 적용할 꺼
	switch (status)
	{
	// 가만히 서있는 경우
	case STATUS_NORMAL:
		// 점프하거나 걸을 수 있음
		// 점프 함수 실행해서 되었는지 판단
		Jump();
		moveFrame += 0.1f;
		if (moveFrame >= 6)
			moveFrame = 0;

		// 왼쪽 키 또는 오른쪽 키 누른 경우
		// 이동하는 녀석으로 상태 변경
		if (INPUT->GetKey(VK_LEFT) || INPUT->GetKey(VK_RIGHT)) {
			status = STATUS_ONLAND;
			moveFrame = 0;
		}
		// 아래쪽 키를 눌렀을 때
		// 밑바닥이 아닌 경우 떨어져야 하므로 떨어지는 상태로 변경
		if (INPUT->GetKeyDown(VK_DOWN) && boxNum != 0) {
			status = STATUS_TOLOW;
			moveFrame = 0;
			// 중력값
			vy = 0;
			y += 30;
		}
		break;

	// 움직이고 있을 때
	case STATUS_ONLAND:
		Move();
		Jump();
		// 박스 밟고 있다 떨어질 때 
		// 내 중심 좌표에서 왼쪽 오른쪽 좌표보다 크거나 작아지면
		if (box[boxNum].left - SIZEX / 2 > x ||
			box[boxNum].right + SIZEX / 2 < x) {
			status = STATUS_TOLOW;
			moveFrame = 0;
			vy = 0;
		}
		if (INPUT->GetKeyUp(VK_LEFT) || INPUT->GetKeyUp(VK_RIGHT)) {
			status = STATUS_NORMAL;
			moveFrame = 0;
		}
		// 아래쪽 키를 눌렀을 때
		// 밑바닥이 아닌 경우 떨어져야 하므로 떨어지는 상태로 변경
		if (INPUT->GetKeyDown(VK_DOWN) && boxNum != 0) {
			status = STATUS_TOLOW;
			moveFrame = 0;
			// 중력값
			vy = 0;
			y += 30;
		}
		break;
	case STATUS_TOUP:
		break;
	case STATUS_TOLOW:
		break;
	case STATUS_LANDING:
		break;
	case STATUS_WALL:
		break;
	case STATUS_CLIMB:
		break;
	default:
		break;
	}
}

void MainGame14::Render(HDC hdc)
{
	HDC memDC = GetBackBuffer()->GetMemDC();
	PatBlt(memDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//=================================================
	character[vector][status][(int)moveFrame]->
		Render(memDC, x - SIZEX / 2, y - SIZEY / 2);
	//=================================================
	this->GetBackBuffer()->Render(hdc);
}

void MainGame14::Move()
{
	if (INPUT->GetKey(VK_LEFT)) {
		// 화면 밖으로 나가지 않게끔
		if (x > SIZEX / 2) {
			x -= SPEED;
		}
		// 방향 0
		vector = 0;
		// 뛰고있는 상태인 경우
		if (status == STATUS_ONLAND) {
			moveFrame += 0.25f;
			if (moveFrame >= 11)
				moveFrame = 0;
		}
	}

	if (INPUT->GetKey(VK_RIGHT)) {
		// 화면 밖으로 나가지 않게끔
		if (x < WINSIZEX - SIZEX / 2) {
			x += SPEED;
		}
		// 방향 1
		vector = 1;
		// 뛰고있는 상태인 경우
		if (status == STATUS_ONLAND) {
			moveFrame += 0.25f;
			if (moveFrame >= 11)
				moveFrame = 0;
		}
	}
}

void MainGame14::Jump()
{
}
