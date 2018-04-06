#include "stdafx.h"
#include "MiniMap.h"


MiniMap::MiniMap()
{
}


MiniMap::~MiniMap()
{
}

HRESULT MiniMap::Init()
{
	IMAGE->AddImage("배경", "images/배경.bmp", -WINSIZEX / 2, 0, 
		WINSIZEX * 2, WINSIZEY, false, RGB(0,0,0));
	IMAGE->AddImage("카메라", "images/카메라.bmp", 0, 0,
		WINSIZEX / 10, WINSIZEY / 10, true, RGB(255, 0, 255));
	IMAGE->AddImage("미니맵", "images/배경.bmp", 0, 0, (WINSIZEX * 2) / 10,
		WINSIZEY / 10, false, RGB(255, 0, 255));
	IMAGE->AddImage("미니캐릭", "images/mini.bmp", 0, 0, 3, 4, true, RGB(255, 0, 255));

	_megaman = IMAGE->AddImage("메가맨", "images/megaman.bmp",
		WINSIZEX / 2, WINSIZEY / 2 + 80, 630, 720, 9, 8, true, RGB(255, 0, 255));
	_megaman->SetFrameX(0);

	_alpha = 0;
	_index = 0;
	_isLeft = false;
	_camera = 0;

	return S_OK;
}

void MiniMap::Release()
{
}

void MiniMap::Update()
{
	if (INPUT->GetKey(VK_LEFT) && _megaman->GetX() > 0) {
		_isLeft = true;
		_ps = PS_RUN;

		if (_megaman->GetX() >= WINSIZEX / 2)
			_megaman->SetX(_megaman->GetX() - 5);
		else if (_camera < 0) _camera += 5;
		else _megaman->SetX(_megaman->GetX() - 5);
	}

	if (INPUT->GetKey(VK_RIGHT) && _megaman->GetX() + 70 < WINSIZEX) {
		_isLeft = false;
		_ps = PS_RUN;

		if (_megaman->GetX() <= WINSIZEX / 2)
			_megaman->SetX(_megaman->GetX() + 5);
		else if (_camera > -WINSIZEX) _camera -= 5;
		else _megaman->SetX(_megaman->GetX() + 5);
	}

	if (!INPUT->GetKey(VK_RIGHT) && !INPUT->GetKey(VK_LEFT)) {
		_ps = PS_IDLE;
	}

	_index = FRAME->GetElapsedTime();
	if (_index < 0) _index = 0;

	if (_isLeft) {
		if (_ps == PS_IDLE) {
			_megaman->SetFrameX(5);
			_megaman->SetFrameY(0);
		}
		if (_ps == PS_RUN) {
			_megaman->SetFrameY(1);
			if (_index > 0.2f) {
				_megaman->SetFrameX(_megaman->GetFrameX() - 1);

				_index = 0;
			}
		}
	}
	else {
		if (_ps == PS_IDLE) {
			_megaman->SetFrameX(4);
			_megaman->SetFrameY(0);
		}
		if (_ps == PS_RUN) {
			_megaman->SetFrameY(0);
			if (_index > 0.2f) {
				_megaman->SetFrameX(_megaman->GetFrameX() + 1);

				_index = 0;
			}
		}
	}
}

void MiniMap::Render()
{
	IMAGE->Render("배경", GetMemDC(), _camera, 0);
	IMAGE->Render("미니맵", GetMemDC(), 700, 50);

	IMAGE->AlphaRender("미니캐릭", GetMemDC(),
		703 + _megaman->GetX() / 10 - _camera / 10,
		50 + _megaman->GetY() / 10, 155);
	IMAGE->Render("카메라", GetMemDC(), 700 - _camera / 10, 50);

	_megaman->FrameRender(GetMemDC(),
		_megaman->GetX(),
		_megaman->GetY(),
		_megaman->GetFrameX(),
		_megaman->GetFrameY());
}
