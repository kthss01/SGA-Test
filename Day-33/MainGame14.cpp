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
	bg->Init("images/�ް��ǹ��.bmp", WINSIZEX, WINSIZEY);

	offsetX = 0;
	offsetY = 0;

	// �̷������� ������ ������ �� �� ����
	// ȭ�� â ũ�Ⱑ ��ȭ�� �Ǿ��� �� ������ �߻���
	// ������ ������ �Ϸ��� ���������� ¥���ϱ��� 
	box[0] = { 0, 572, WINSIZEX, WINSIZEY };
	box[1] = { 704, 486, 1025, 510 };
	box[2] = { 1026, 223, WINSIZEX, 233 };
	box[3] = { 960, 190, 1026, 260 };

	for (int i = 0; i < 11; i++) {
		character[0][STATUS_ONLAND][i] = new Image;
		sprintf_s(str, "images/���ʰȱ�%d.bmp", i + 1);
		character[0][STATUS_ONLAND][i]->Init(str, SIZEX, SIZEY,
			true, RGB(255, 0, 255));
		character[1][STATUS_ONLAND][i] = new Image;
		sprintf_s(str, "images/�����ʰȱ�%d.bmp", i + 1);
		character[1][STATUS_ONLAND][i]->Init(str, SIZEX, SIZEY,
			true, RGB(255, 0, 255));
	}

	for (int i = 0; i < 6; i++) {
		character[0][STATUS_NORMAL][i] = new Image;
		sprintf_s(str, "images/�������%d.bmp", i + 1);
		character[0][STATUS_NORMAL][i]->Init(str, SIZEX, SIZEY,
			true, RGB(255, 0, 255));
		character[1][STATUS_NORMAL][i] = new Image;
		sprintf_s(str, "images/���������%d.bmp", i + 1);
		character[1][STATUS_NORMAL][i]->Init(str, SIZEX, SIZEY,
			true, RGB(255, 0, 255));
	}

	for (int i = 0; i < 5; i++) {
		character[0][STATUS_TOUP][i] = new Image;
		sprintf_s(str, "images/��������%d.bmp", i + 1);
		character[0][STATUS_TOUP][i]->Init(str, SIZEX, SIZEY,
			true, RGB(255, 0, 255));
		character[1][STATUS_TOUP][i] = new Image;
		sprintf_s(str, "images/����������%d.bmp", i + 1);
		character[1][STATUS_TOUP][i]->Init(str, SIZEX, SIZEY,
			true, RGB(255, 0, 255));

		character[0][STATUS_TOLOW][i] = new Image;
		sprintf_s(str, "images/��������%d.bmp", i + 6);
		character[0][STATUS_TOLOW][i]->Init(str, SIZEX, SIZEY,
			true, RGB(255, 0, 255));
		character[1][STATUS_TOLOW][i] = new Image;
		sprintf_s(str, "images/����������%d.bmp", i + 6);
		character[1][STATUS_TOLOW][i]->Init(str, SIZEX, SIZEY,
			true, RGB(255, 0, 255));
	}

	// ���� 11 12 �� ���� ���
	character[0][STATUS_LANDING][0] = new Image;
	character[0][STATUS_LANDING][0]->Init("images/��������11.bmp",
		SIZEX, SIZEY, true, RGB(255, 0, 255));
	character[0][STATUS_LANDING][1] = new Image;
	character[0][STATUS_LANDING][1]->Init("images/��������12.bmp",
		SIZEX, SIZEY, true, RGB(255, 0, 255));

	character[1][STATUS_LANDING][0] = new Image;
	character[1][STATUS_LANDING][0]->Init("images/����������11.bmp",
		SIZEX, SIZEY, true, RGB(255, 0, 255));
	character[1][STATUS_LANDING][1] = new Image;
	character[1][STATUS_LANDING][1]->Init("images/����������12.bmp",
		SIZEX, SIZEY, true, RGB(255, 0, 255));

	// 1 ���� �Ŵ޸��� ��� 2,3 �� �ö󰡴� ���
	character[0][STATUS_WALL][0] = new Image;
	character[0][STATUS_WALL][0]->Init("images/���ʺ����1.bmp",
		SIZEX, SIZEY, true, RGB(255, 0, 255));

	character[0][STATUS_CLIMB][0] = new Image;
	character[0][STATUS_CLIMB][0]->Init("images/���ʺ����2.bmp",
		SIZEX, SIZEY, true, RGB(255, 0, 255));
	character[0][STATUS_CLIMB][1] = new Image;
	character[0][STATUS_CLIMB][1]->Init("images/���ʺ����3.bmp",
		SIZEX, SIZEY, true, RGB(255, 0, 255));

	character[1][STATUS_WALL][0] = new Image;
	character[1][STATUS_WALL][0]->Init("images/�����ʺ����1.bmp",
		SIZEX, SIZEY, true, RGB(255, 0, 255));

	character[1][STATUS_CLIMB][0] = new Image;
	character[1][STATUS_CLIMB][0]->Init("images/�����ʺ����2.bmp",
		SIZEX, SIZEY, true, RGB(255, 0, 255));
	character[1][STATUS_CLIMB][1] = new Image;
	character[1][STATUS_CLIMB][1]->Init("images/�����ʺ����3.bmp",
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
				// �����ϸ� ����ڴٴ°� �� �ִ°� �� �ٸ���
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

	// ���� �ִϸ��̼� Ŭ���� ��� ������ ������ ���� �� ��
	// Move() Jump()���� ���� ��� �ٲ��� ������ ��
	switch (status)
	{
	// ������ ���ִ� ���
	case STATUS_NORMAL:
		// �����ϰų� ���� �� ����
		// ���� �Լ� �����ؼ� �Ǿ����� �Ǵ�
		Jump();
		moveFrame += 0.1f;
		if (moveFrame >= 6)
			moveFrame = 0;

		// ���� Ű �Ǵ� ������ Ű ���� ���
		// �̵��ϴ� �༮���� ���� ����
		if (INPUT->GetKey(VK_LEFT) || INPUT->GetKey(VK_RIGHT)) {
			status = STATUS_ONLAND;
			moveFrame = 0;
		}
		// �Ʒ��� Ű�� ������ ��
		// �عٴ��� �ƴ� ��� �������� �ϹǷ� �������� ���·� ����
		if (INPUT->GetKeyDown(VK_DOWN) && boxNum != 0) {
			status = STATUS_TOLOW;
			moveFrame = 0;
			// �߷°�
			vy = 0;
			y += 30;
		}
		break;

	// �����̰� ���� ��
	case STATUS_ONLAND:
		Move();
		Jump();
		// �ڽ� ��� �ִ� ������ �� 
		// �� �߽� ��ǥ���� ���� ������ ��ǥ���� ũ�ų� �۾�����
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
		// �Ʒ��� Ű�� ������ ��
		// �عٴ��� �ƴ� ��� �������� �ϹǷ� �������� ���·� ����
		if (INPUT->GetKeyDown(VK_DOWN) && boxNum != 0) {
			status = STATUS_TOLOW;
			moveFrame = 0;
			// �߷°�
			vy = 0;
			y += 30;
		}
		break;
	case STATUS_TOUP:
		Move();
		// ���� �����ϰ� ������
		//Jump();
		// ���� �ö󰡴� �ִϸ��̼� ��Ȳ�̸�
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
			// x, y �̹��� �߽���
			if (IntersectRect(&temp, &box[i],
				&RectMakeCenter(x, y + SIZEY / 2, SIZEX, 2))
				// �� �̻� ��ġ�� �Ǹ� �������� (�浹�� ���� �ʰ�)
				&& x > box[i].left && x < box[i].right)
			{
				boxNum = i;
				y = box[i].top - SIZEY / 2;
				moveFrame = 0;
				status = STATUS_LANDING;
			}
		}
		// ����� ��
		// box[3]�� box[2]���� ��¦ ũ�� �Ǿ����� �׷��� �ɸ��°� box[2]�� �ϴ°�
		if (IntersectRect(&temp, &box[3], &RectMakeCenter(x, y, 2, 2))
			// ������ �ٶ󺸰� ���� ��
			&& vector == 1) {
			x = box[2].left - 35;
			y = box[2].top + 35;
			moveFrame = 0;
			status = STATUS_WALL;
		}
		break;
	// ���� ���ڸ��� ����Ǵ� �༮
	// ���� ���� �� �����Ӹ� �ϰ� STATUS_NORMAL�� ����
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
		// moveFrame�� 0�̸�
		if (moveFrame < 1) {
			y -= 10;
		}
		else if (moveFrame <= 2) {
			y -= 5;
			x += 5;
		}
		else {
			moveFrame = 0;
			// Low�� �ٲ��� ���� : Low���� �ٴڿ� ������ Normal�� �ٲ� �� ������
			status = STATUS_TOLOW;
		}
		break;
	default:
		break;
	}

	offsetX++;
	offsetY++;

	// �ʿ��ϸ� ���߿� �ᵵ ����
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
		// ȭ�� ������ ������ �ʰԲ�
		if (x > SIZEX / 2) {
			x -= SPEED;
		}
		// ���� 0
		vector = 0;
		// �ٰ��ִ� ������ ���
		if (status == STATUS_ONLAND) {
			moveFrame += 0.25f;
			if (moveFrame >= 11)
				moveFrame = 0;
		}
	}

	if (INPUT->GetKey(VK_RIGHT)) {
		// ȭ�� ������ ������ �ʰԲ�
		if (x < WINSIZEX - SIZEX / 2) {
			x += SPEED;
		}
		// ���� 1
		vector = 1;
		// �ٰ��ִ� ������ ���
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
		// �ѹ� ������ �ϱ� ���ؼ� ���� �ٲٰ� �ű⼭�� Jump() �Լ� ȣ�� ���ϰ�
		// ���� �����ϰ� ������ �ű⼭�� Jump() ȣ���ϸ��
		status = STATUS_TOUP;
	}
}
