#include "stdafx.h"
#include "MainGame12.h"


MainGame12::MainGame12()
{
}


MainGame12::~MainGame12()
{
}

HRESULT MainGame12::Init()
{
	GameNode::Init();

	// 초기화 해주는 함수
	memset(_bead, 0, sizeof(_bead));
	//memset(_bead, 0, sizeof(tagBead) * BEADMAX);

	for (int i = 0; i < BEADMAX; i++) {
		_bead[i].radius = 20.0f;
		_bead[i].speed = 5.0f;
		// 삼항 연산자 (조건) ? 참 : 거짓;
		_bead[i].angle = (i == 0) ? RND->GetInt(7) : _bead[i - 1].angle;
		_bead[i].x = (i == 0) ? RND->GetFromInto(100, WINSIZEX - 100)
			: _bead[i].x - cosf(_bead[i].angle) *
			(_bead[i - 1].radius * 2 + _bead[i].radius * 2);
		_bead[i].y = (i == 0) ? RND->GetFromInto(100, WINSIZEY - 100)
			: _bead[i].y - (-sinf(_bead[i].angle)) *
			(_bead[i - 1].radius * 2 + _bead[i].radius * 2);
	}

	image[0] = new Image;
	image[0]->Init("images/apple.bmp",
		_bead[0].radius + 10, _bead[0].radius + 10, true, RGB(255, 0, 255));

	image[1] = new Image;
	image[1]->Init("images/배경 화면.bmp",
		_bead[0].radius + 10, _bead[0].radius + 10, true, RGB(255, 0, 255));

	image[2] = new Image;
	image[2]->Init("images/apple.bmp",
		_bead[0].radius + 10, _bead[0].radius + 10, true, RGB(255, 0, 255));
	
	bg = new Image;
	bg->Init("images/배경 화면.bmp", WINSIZEX, WINSIZEY);
	
	x = y = 0;
	alpha = 0;

	return S_OK;
}

void MainGame12::Release()
{
	GameNode::Release();
	for(int i=0; i<3; i++)
		SAFE_DELETE(image[i]);	// new 할당 받은 변수는 SAFE_DELETE
	SAFE_DELETE(bg);
}

void MainGame12::Update()
{
	GameNode::Update();

	if (INPUT->GetKey('W')) { y += 1; }
	if (INPUT->GetKey('S')) { y -= 1; }
	if (INPUT->GetKey('A')) { x -= 1; }
	if (INPUT->GetKey('D')) { x += 1; }
	if (INPUT->GetKey('Q')) { alpha += 1; }
	if (INPUT->GetKey('E')) { alpha -= 1; }

	BeadMove();
}

void MainGame12::Render(HDC hdc)
{
	HDC memDC = this->GetBackBuffer()->GetMemDC();
	PatBlt(memDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//=================================================

	//bg->Render(memDC, 100, 100, 200 + x, 200 + y, 300, 300);
	//bg->AlphaRender(memDC, alpha); // 0 이 투명 255 불투명
	
	//image[0]->Render(memDC);
	image[0]->AlphaRender(memDC, 128);

	//for (int i = 0; i < BEADMAX; i++) {
	//	//EllipseMakeCenter(memDC, _bead[i].x, _bead[i].y, _bead[i].radius);
	//	//image[0]->Render(memDC, _bead[i].x, _bead[i].y);
	//	if (i < 1) {
	//		// 머리
	//		image[0]->Render(memDC, _bead[i].x, _bead[i].y);
	//	}
	//	else if (i < BEADMAX - 2) {
	//		// 몸통
	//		image[1]->Render(memDC, _bead[i].x, _bead[i].y);
	//	}
	//	else
	//	{
	//		// 꼬리
	//		image[2]->Render(memDC, _bead[i].x, _bead[i].y);
	//	}
	//}

	//=================================================
	this->GetBackBuffer()->Render(hdc);
}

void MainGame12::BeadMove()
{
	for (int i = 0; i < BEADMAX; i++) {
		if (i == 0) {
			_bead[i].x += cosf(_bead[i].angle) * _bead[i].speed;
			_bead[i].y += -sinf(_bead[i].angle) * _bead[i].speed;

			// 벽 충돌
			// 위치 보정 필요성은
			// 속도가 너무 높았을 때 뛰쳐나가지 않게 하는거임
			// 속도 조절 하면 안해도 되는 경우
			// 왼쪽 
			if (_bead[i].x - _bead[i].radius < 0)
				_bead[i].angle = PI - _bead[i].angle;
			// 오른쪽
			if (_bead[i].x + _bead[i].radius > WINSIZEX)
				_bead[i].angle = PI - _bead[i].angle;
			// 위
			if (_bead[i].y - _bead[i].radius < 0)
				_bead[i].angle = -_bead[i].angle;
			// 아래
			if (_bead[i].y + _bead[i].radius > WINSIZEY)
				_bead[i].angle = -_bead[i].angle;
		}
		else {
			// 이런식으로 해두 되는데 컴퓨터 성능에 다라 
			// 한꺼번에 회전하는 경우도 있음 이 방식은 좋지 않음
			//_bead[i-1].angle = _bead[i-1].angle;

			float distance = GetDistance(_bead[i].x, _bead[i].y,
				_bead[i - 1].x, _bead[i - 1].y);

			// _bead[i].radius + _bead[i-1].radius
			if (_bead[i].radius * 2 < distance) {

				// GetAngle 넣을때 인수 반대로 넣으면 각도 차 날 수 있음 180 정도
				// 그래서 포탄 발사 때 원끼리 충돌할 때 반대로 넣는거
				_bead[i].angle = GetAngle(
					_bead[i].x, _bead[i].y, _bead[i - 1].x, _bead[i - 1].y);

				_bead[i].x = _bead[i - 1].x - cosf(_bead[i].angle) *
					_bead[i].radius * 2;
				_bead[i].y = _bead[i - 1].y - (-sinf(_bead[i].angle)) *
					_bead[i].radius * 2;
			}

			_bead[i].x += cosf(_bead[i].angle) * _bead[i].speed;
			_bead[i].y += -sinf(_bead[i].angle) * _bead[i].speed;
		}
	}
}
