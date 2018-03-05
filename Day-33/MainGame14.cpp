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

	// �̷������� ������ ������ �� �� ����
	// ȭ�� â ũ�Ⱑ ��ȭ�� �Ǿ��� �� ������ �߻���
	// ������ ������ �Ϸ��� ���������� ¥���ϱ��� 
	box[0] = { 0, 572, WINSIZEX, WINSIZEY };
	box[1] = { 704, 486, 1025, 510 };
	box[2] = { 1026, 223, WINSIZEX, 223 };
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
}
