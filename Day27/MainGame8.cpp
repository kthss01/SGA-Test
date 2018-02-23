#include "stdafx.h"
#include "MainGame8.h"


MainGame8::MainGame8()
{
}


MainGame8::~MainGame8()
{
}

HRESULT MainGame8::Init()
{
	GameNode3::Init();

	for (int i = 0; i < BULLETMAX; i++) {
		_bullet[i].isFire = false;
	}

	_player = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 100, 100);

	//rc[0] = RectMakeCenter(WINSIZEX / 2 - 100, WINSIZEY / 2, 100, 100);
	//rc[1] = RectMakeCenter(WINSIZEX / 2 + 100, WINSIZEY / 2, 100, 100);

	//// sec
	//arrow[0].length = 200;
	//arrow[0].angle = 6.0f;

	//// min
	//arrow[1].length = 150;
	//arrow[1].angle = 6.0f;

	//// hour
	//arrow[2].length = 100;
	//arrow[2].angle = 30.0f;

	//startPosition = { WINSIZEX / 2, WINSIZEY / 2 };

	return S_OK;
}

void MainGame8::Release()
{
	GameNode3::Release();
}

void MainGame8::Update()
{
	GameNode3::Update();

	if (INPUT->GetKey(VK_SPACE)) {
		for (int i = 0; i < BULLETMAX; i++) {
			if (_bullet[i].isFire == true) continue;

			_bullet[i].isFire = true;
			_bullet[i].x = _player.left + (_player.right - _player.left) / 2;
			_bullet[i].y = _player.top;
			_bullet[i].rc = RectMakeCenter(_bullet[i].x, _bullet[i].y, 10, 10);
			break;
		}
	}
	for (int i = 0; i < BULLETMAX; i++) {
		if (_bullet[i].isFire == false) continue;

		_bullet[i].y -= 5.0f;			
		_bullet[i].rc = RectMakeCenter(_bullet[i].x, _bullet[i].y, 10, 10);
	}

	for (int i = 0; i < 50; i++) {
		if (_bullet[i].isFire == false) continue;

		if (_bullet[i].rc.bottom < 0)
			_bullet[i].isFire = false;
	}

	if (INPUT->GetKey(VK_LEFT)) {
		_player.left -= 3.0f;
		_player.right -= 3.0f;
	}

	if (INPUT->GetKey(VK_RIGHT)) {
		_player.left += 3.0f;
		_player.right += 3.0f;
	}

	if (INPUT->GetKey(VK_DOWN)) {
		_player.top += 3.0f;
		_player.bottom += 3.0f;
	}

	if (INPUT->GetKey(VK_UP)) {
		_player.top -= 3.0f;
		_player.bottom -= 3.0f;
	}

	//if (INPUT->GetKey(VK_LBUTTON)) {
	//	rc[0] = RectMakeCenter(g_ptMouse.x, g_ptMouse.y, 100, 100);
	//}

	//if (Collision() == true) {
	//	float angle = GetAngle();
	//	rc[1].left += cos(angle) * 5.0f;
	//	rc[1].right += cos(angle) * 5.0f;

	//	rc[1].top += -sin(angle) * 5.0f;
	//	rc[1].bottom += -sin(angle) * 5.0f;
	//}

	//GetLocalTime(&st);

	//arrow[0].endPosition.x = startPosition.x
	//	+ cos(st.wSecond * arrow[0].angle * PI / 180
	//	- 90.0f * PI / 180) * arrow[0].length;
	//arrow[0].endPosition.y = startPosition.y
	//	+ sin(st.wSecond * arrow[0].angle * PI / 180
	//	- 90.0f * PI / 180) * arrow[0].length;

	//arrow[1].endPosition.x = startPosition.x
	//	+ cos(st.wMinute * arrow[1].angle * PI / 180
	//	- 90.0f * PI / 180) * arrow[1].length;
	//arrow[1].endPosition.y = startPosition.y
	//	+ sin(st.wMinute * arrow[1].angle * PI / 180
	//	- 90.0f * PI / 180) * arrow[1].length;

	//arrow[2].endPosition.x = startPosition.x
	//	+ cos((st.wHour % 12) * arrow[2].angle * PI / 180
	//	- 90.0f * PI / 180) * arrow[2].length;
	//arrow[2].endPosition.y = startPosition.y
	//	+ sin((st.wHour % 12) * arrow[2].angle * PI / 180
	//	- 90.0f * PI / 180) * arrow[2].length;
}

void MainGame8::Render(HDC hdc)
{
	//test
	HDC memDC = this->GetBackBuffer()->GetMemDC();
	// 배경 화면 흰색으로 칠해주는 함수
	PatBlt(memDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//=================================================
	
	for (int i = 0; i < BULLETMAX; i++) {
		if (_bullet[i].isFire == false) continue;
		Rectangle(memDC, _bullet[i].rc.left, _bullet[i].rc.top,
			_bullet[i].rc.right, _bullet[i].rc.bottom);
	}

	Rectangle(memDC, _player.left, _player.top, _player.right, _player.bottom);

	//for (int i = 0; i < 2; i++)
	//	Ellipse(memDC, rc[i].left, rc[i].top, rc[i].right, rc[i].bottom);

	//char str[128];
	//sprintf_s(str, "%f", GetAngle());
	//TextOut(memDC, 10, 10, str, strlen(str));

	/*Ellipse(memDC, startPosition.x - 200, startPosition.y - 200,
		startPosition.x + 200, startPosition.y + 200);

	for (int i = 0; i < 3; i++) {
		LineMake(memDC, startPosition, arrow[i].endPosition);
	}*/

	//=================================================
	this->GetBackBuffer()->Render(hdc);
}

bool MainGame8::Collision()
{
	POINT center1;
	POINT center2;

	center1.x = rc[0].left + (rc[0].right - rc[0].left) / 2;
	center1.y = rc[0].top + (rc[0].bottom - rc[0].top) / 2;
	center2.x = rc[1].left + (rc[1].right - rc[1].left) / 2;
	center2.y = rc[1].top + (rc[1].bottom - rc[1].top) / 2;

	// 문제 생겨서 다시 만듬
	int deltaX = center2.x - center1.x;
	int deltaY = center2.y - center1.y;

	//// rc 크기(너비) 50으로 줄꺼 중심점 구하기 귀찮으므로
	//int deltaX = (rc[1].left + 50) - (rc[0].left + 50);
	//// 그냥 같은 크기 이므로 top에서 top 빼는걸로
	//int deltaY = rc[1].top - rc[0].top;

	float distance = sqrt(deltaX * deltaX + deltaY * deltaY);

	if (100 > distance) {
		return true;
	}
	return false;
}

float MainGame8::GetAngle()
{
	POINT center1;
	POINT center2;

	center1.x = rc[0].left + (rc[0].right - rc[0].left) / 2;
	center1.y = rc[0].top + (rc[0].bottom - rc[0].top) / 2;

	center2.x = rc[1].left + (rc[1].right - rc[1].left) / 2;
	center2.y = rc[1].top + (rc[1].bottom - rc[1].top) / 2;

	// 문제 생겨서 다시 만듬
	// 선생님 따라 못해서 계속 틀렸엇는데
	// abs안쓰시고 그냥 뺀 후에 나중에 조건 처리하셨음
	int deltaX = center2.x - center1.x;
	int deltaY = center2.y - center1.y;

	//// rc 크기(너비) 50으로 줄꺼 중심점 구하기 귀찮으므로
	//// deltaX 음수가 나오면 안됨 abs 사용 절대값 함수
	//int deltaX = abs((rc[1].left + 50) - (rc[0].left + 50));
	//// 그냥 같은 크기 이므로 top에서 top 빼는걸로
	//int deltaY = rc[1].top - rc[0].top;

	float distance = sqrt(deltaX * deltaX + deltaY * deltaY);

	float angle = acos(deltaX / distance);	// PI 각도로 나옴

	if (center2.y > center1.y) {
		angle = 2 * PI - angle;
		if (angle >= 2 * PI) angle -= 2 * PI;
	}

	return angle;
}
