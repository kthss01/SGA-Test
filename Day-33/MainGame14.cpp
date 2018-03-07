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

	offsetX = 0;
	offsetY = 0;

	// 이런식으로 설정시 문제가 될 수 있음
	// 화면 창 크기가 변화가 되었을 때 문제가 발생함
	// 문제가 없도록 하려면 기준점으로 짜야하긴함 
	box[0] = { 0, 572, WINSIZEX, WINSIZEY };
	box[1] = { 704, 486, 1025, 510 };
	box[2] = { 1026, 223, WINSIZEX, 233 };
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

//	y = 1000 - SIZEY / 2;

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
		Move();
		// 이중 점프하고 싶으면
		//Jump();
		// 내가 올라가는 애니메이션 상황이면
		if (moveFrame < 5) moveFrame += 0.15f;
		if (moveFrame >= 5) moveFrame = 2;
		y += vy;
		vy += GRAVITY;
		if (vy >= 0) {
			status = STATUS_TOLOW;
			moveFrame = 0;
		}
		break;
	case STATUS_TOLOW:
		Move();
		if (moveFrame < 5) moveFrame += 0.15f;
		if (moveFrame >= 5) moveFrame = 1;
		y += vy;
		vy += GRAVITY;
		for (int i = 0; i < 3; i++) {
			// x, y 이미지 중심점
			if (IntersectRect(&temp, &box[i],
				&RectMakeCenter(x, y + SIZEY / 2, SIZEX, 2))
				// 반 이상 걸치게 되면 떨어지게 (충돌이 되지 않게)
				&& x > box[i].left && x < box[i].right)
			{
				boxNum = i;
				y = box[i].top - SIZEY / 2;
				moveFrame = 0;
				status = STATUS_LANDING;
			}
		}
		// 벽잡는 거
		// box[3]은 box[2]보다 살짝 크게 되어있음 그래서 걸리는건 box[2]로 하는거
		if (IntersectRect(&temp, &box[3], &RectMakeCenter(x, y, 2, 2))
			// 오른쪽 바라보고 있을 때
			&& vector == 1) {
			x = box[2].left - 35;
			y = box[2].top + 35;
			moveFrame = 0;
			status = STATUS_WALL;
		}
		break;
	// 땅에 닿자마자 실행되는 녀석
	// 닿은 순간 몇 프레임만 하고 STATUS_NORMAL로 변경
	case STATUS_LANDING:
		moveFrame += 0.5f;
		if (moveFrame >= 2)
			status = STATUS_NORMAL;
		break;
	case STATUS_WALL:
		Jump();
		if (INPUT->GetKeyDown(VK_UP))
			status = STATUS_CLIMB;
		break;
	case STATUS_CLIMB:
		moveFrame += 0.1;
		// moveFrame이 0이면
		if (moveFrame < 1) {
			y -= 10;
		}
		else if (moveFrame <= 2) {
			y -= 5;
			x += 5;
		}
		else {
			moveFrame = 0;
			// Low로 바꿔준 이유 : Low에서 바닥에 닿으면 Normal로 바뀔 수 있으니
			status = STATUS_TOLOW;
		}
		break;
	default:
		break;
	}

	offsetX++;
	offsetY++;

	// 필요하면 나중에 써도 좋음
	//====================== Debug =====================//
	if (INPUT->GetKeyDown(VK_F11)) {
		isDebug = !isDebug;
	}
	//==================================================//
}

void MainGame14::Render(HDC hdc)
{
	HDC memDC = GetBackBuffer()->GetMemDC();
	PatBlt(memDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//=================================================
	{
		//bg->Render(memDC);
		//bg->Render(memDC, 0, 0, WINSIZEX / 2, 0, WINSIZEX, WINSIZEY);
		//bg->Render(memDC, WINSIZEX / 2, 0, 
		//	0, 0, WINSIZEX / 2, WINSIZEY);

		bg->LoopRender(memDC, 
			&RectMake(0, 0, WINSIZEX/2, WINSIZEY/2), offsetX, offsetY);

		character[vector][status][(int)moveFrame]->
			Render(memDC, x - SIZEX / 2, y - SIZEY / 2);
	}
	//==================   Debug   ====================
	if (isDebug)
	{
		for (int i = 0; i < 4; i++) {
			Rectangle(memDC, box[i].left, box[i].top, box[i].right,
				box[i].bottom);
		}
	}
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
	if (INPUT->GetKeyDown(VK_SPACE)) {
		moveFrame = 0;
		vy = JUMP;
		// 한번 점프만 하기 위해서 상태 바꾸고 거기서는 Jump() 함수 호출 안하게
		// 이중 점프하고 싶으면 거기서도 Jump() 호출하면됨
		status = STATUS_TOUP;
	}
}
