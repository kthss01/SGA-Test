#include "stdafx.h"
#include "Ship.h"


Ship::Ship()
{
}


Ship::~Ship()
{
}

HRESULT Ship::Init(const char * imageName, int x, int y)
{
	_image = IMAGE->FindImage(imageName);

	_x = x;
	_y = y;

	_angle = 0.0f;
	_rc = RectMakeCenter(
		_x, _y, _image->GetFrameWidth(), _image->GetFrameHeight());

	_speed = 0;
	_radius = _image->GetFrameHeight() / 2;


	return S_OK;
}

void Ship::Release()
{
}

void Ship::Update()
{
	KeyControl();
	Move();
}

void Ship::Render()
{
	Draw();
}

void Ship::Draw()
{
	_image->FrameRender(GetMemDC(), _rc.left, _rc.top);

	char str[128];
	sprintf_s(str, "%d도 %3.2f", int(_angle * 180 / PI), _speed);
	TextOut(GetMemDC(), _rc.left, _rc.top - 15, str, strlen(str));
}

void Ship::KeyControl()
{
	if (INPUT->GetKey(VK_LEFT)) _angle += 0.04f;
	if (INPUT->GetKey(VK_RIGHT)) _angle -= 0.04f;

	if (INPUT->GetKey(VK_UP)) _speed += 0.04f;
	if (INPUT->GetKey(VK_DOWN)) _speed -= 0.04f;
}

void Ship::Move()
{
	int frame;
	float angle;
	
	if (_angle <= 0) _angle += PI * 2;
	if (_angle >= PI * 2) _angle -= PI * 2;

	// 각도 (프레임 계산 해줄)
	// 각도는 현재 각도에서 16등분 할꺼
	angle = _angle + (PI / 16);

	frame = int(angle / (PI / 8));

	if (frame == 16) frame = 0;

	_image->SetFrameX(frame);

	float elapsedTime = FRAME->GetElapsedTime();
	float moveSpeed = elapsedTime * 100;

	_x += cosf(angle) * _speed * moveSpeed;
	_y -= sinf(angle) * _speed * moveSpeed;

	_rc = RectMakeCenter(
		_x, _y, _image->GetFrameWidth(), _image->GetFrameHeight());
}
