#include "stdafx.h"
#include "MainGame10.h"


MainGame10::MainGame10()
{
}


MainGame10::~MainGame10()
{
}

HRESULT MainGame10::Init()
{
	GameNode::Init();
	
	//// �ʱ�ȭ ���ִ� �Լ�
	//memset(_bead, 0, sizeof(_bead));
	////memset(_bead, 0, sizeof(tagBead) * BEADMAX);

	//for (int i = 0; i < BEADMAX; i++) {
	//	_bead[i].radius = 20.0f;
	//	_bead[i].speed = 5.0f;
	//	// ���� ������ (����) ? �� : ����;
	//	_bead[i].angle = (i == 0) ? RND->GetInt(7) : _bead[i - 1].angle;
	//	_bead[i].x = (i == 0) ? RND->GetFromInto(100, WINSIZEX - 100)
	//		: _bead[i].x - cosf(_bead[i].angle) *
	//		(_bead[i - 1].radius * 2 + _bead[i].radius * 2);
	//	_bead[i].y = (i == 0) ? RND->GetFromInto(100, WINSIZEY - 100)
	//		: _bead[i].y - (-sinf(_bead[i].angle)) *
	//		(_bead[i - 1].radius * 2 + _bead[i].radius * 2);
	//}

	//for (int i = 0; i < 5; i++)
	//{
	//	for (int j = 0; j < 4; j++) {
	//		m_block[i * 4 + j] = RectMakeCenter(
	//			100 + 100 * i + j % 2 * 50, 100 + 100 * j, 100, 100);
	//	}
	//}

	m_rc = RectMakeCenter(WINSIZEX / 2 + 100, WINSIZEY / 2, 100, 100);
	m_el = RectMakeCenter(WINSIZEX / 2 - 100, WINSIZEY / 2, 100, 100);

	m_radius = 50;
	m_touch = false;

	return S_OK;
}

void MainGame10::Release()
{
	GameNode::Release();
}

void MainGame10::Update()
{
	GameNode::Update();

	//if (INPUT->GetKey(VK_LEFT)) {
	//	_bead[0].angle += 0.05f;
	//}
	//if (INPUT->GetKey(VK_RIGHT)) {
	//	_bead[0].angle -= 0.05f;
	//}

	//BeadMove();

	m_elCenter.x = m_el.left + m_radius;
	m_elCenter.y = m_el.top + m_radius;

	if (PtInRect(&m_rc, g_ptMouse) && m_touch) {
		m_rc = RectMakeCenter(g_ptMouse.x, g_ptMouse.y, 100, 100);
	}

	//// ���� �簢���� �浹 �˻� 1��
	//// ���� �ܼ��� ���
	//for (int i = 0; i < 360; i++) {
	//	POINT collisionPoint;
	//	collisionPoint.x = m_elCenter.x + cosf(i * PI / 180) * m_radius;
	//	collisionPoint.y = m_elCenter.y -sinf(i * PI / 180) * m_radius;

	//	if (PtInRect(&m_rc, collisionPoint)) {
	//		// m_ptSave : ������ ��� �κ� ��������� ���� ��ǥ���� ������� �༮
	//		m_el = RectMakeCenter(
	//			g_ptMouse.x - m_ptSave.x,
	//			g_ptMouse.y - m_ptSave.y,
	//			100, 100);

	//	}
	//}

	// ���� �簢�� �浹 �˻� 2��
	if (RectInCircle(&m_rc, m_elCenter, m_radius))
	{
		m_el = RectMakeCenter(
			g_ptMouse.x - m_ptSave.x,
			g_ptMouse.y - m_ptSave.y,
			100, 100);
	}

	if (INPUT->GetKey(VK_LBUTTON)) {
		m_touch = true;				// ���� �߽��� ���ϴ� �����
		m_ptSave.x = g_ptMouse.x - (m_el.left + m_el.right) / 2;
		m_ptSave.y = g_ptMouse.y - (m_el.top + m_el.bottom) / 2;
	}

	if (INPUT->GetKeyUp(VK_LBUTTON)) {
		m_touch = false;
	}



//  // �Ŀ� ������ ����� ���
//	if (INPUT->GetKeyDown(VK_SPACE)) {
//		_power = 1.0f;
//	}
//
//	if (INPUT->GetKey(VK_SPACE)) {
//		_power += 0.1f;
//		if(_power > 10.0f)
//			_power = 10.0f;
//	}
//	if (INPUT->GetKeyUp(VK_SPACE)) {
//		m_bullet[i].speed = _power;
//	}
}

void MainGame10::Render(HDC hdc)
{
	HDC memDC = this->GetBackBuffer()->GetMemDC();
	PatBlt(memDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//=================================================
	
	/*for (int i = 0; i < BEADMAX; i++)
		EllipseMakeCenter(memDC, _bead[i].x, _bead[i].y, _bead[i].radius);*/

	Rectangle(memDC, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
	Ellipse(memDC, m_el.left, m_el.top, m_el.right, m_el.bottom);

	//for (int i = 0; i < 20; i++) {
	//	Rectangle(memDC, m_block[i].left, m_block[i].top, m_block[i].right, m_block[i].bottom);
	//}

	//=================================================
	this->GetBackBuffer()->Render(hdc);
}

void MainGame10::BeadMove()
{
	for (int i = 0; i < BEADMAX; i++) {
		if (i == 0) {
			_bead[i].x += cosf(_bead[i].angle) * _bead[i].speed;
			_bead[i].y += -sinf(_bead[i].angle) * _bead[i].speed;

			// �� �浹
			// ��ġ ���� �ʿ伺��
			// �ӵ��� �ʹ� ������ �� ���ĳ����� �ʰ� �ϴ°���
			// �ӵ� ���� �ϸ� ���ص� �Ǵ� ���
			// ���� 
			if (_bead[i].x - _bead[i].radius < 0)
				_bead[i].angle = PI - _bead[i].angle;
			// ������
			if (_bead[i].x + _bead[i].radius > WINSIZEX)
				_bead[i].angle = PI - _bead[i].angle;
			// ��
			if (_bead[i].y - _bead[i].radius < 0)
				_bead[i].angle = -_bead[i].angle;
			// �Ʒ�
			if (_bead[i].y + _bead[i].radius > WINSIZEY)
				_bead[i].angle = -_bead[i].angle;
		}
		else {
			// �̷������� �ص� �Ǵµ� ��ǻ�� ���ɿ� �ٶ� 
			// �Ѳ����� ȸ���ϴ� ��쵵 ���� �� ����� ���� ����
			//_bead[i-1].angle = _bead[i-1].angle;

			float distance = GetDistance(_bead[i].x, _bead[i].y,
				_bead[i - 1].x, _bead[i - 1].y);

			// _bead[i].radius + _bead[i-1].radius
			if (_bead[i].radius * 2 < distance) {

				// GetAngle ������ �μ� �ݴ�� ������ ���� �� �� �� ���� 180 ����
				// �׷��� ��ź �߻� �� ������ �浹�� �� �ݴ�� �ִ°�
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

bool MainGame10::RectInCircle(RECT * rect, POINT circleCenter, float radius)
{
	// ���� �߽����� �簢�� �𼭸��� �ƴ� �簢�� ���̿� ���� ��

	// left right ���̿� ���� �߽��� x �� ����ְų�
	if (rect->left <= circleCenter.x && circleCenter.x <= rect->right
		|| rect->top <= circleCenter.y && circleCenter.y <= rect->bottom) {
		
		// ������ �簢������ ���� ��������ŭ Ŀ�� �簢���� ����
		RECT rcEx = {
			rect->left - radius,
			rect->top - radius,
			rect->right + radius,
			rect->bottom + radius
		};

		// �� �簢�� �ȿ� ���� �� ������ �浹
		return PtInRect(&rcEx, circleCenter);
	}
	// �𼭸� �ʿ� ���� ��� �ʿ�
	else {
		float distance[4];
		// ���� �� �𼭸�
		distance[0] = GetDistance(circleCenter.x, circleCenter.y,
			rect->left, rect->top);
		// ������ ��
		distance[1] = GetDistance(circleCenter.x, circleCenter.y,
			rect->right, rect->top);
		// ���� �Ʒ�
		distance[2] = GetDistance(circleCenter.x, circleCenter.y,
			rect->left, rect->bottom);
		// ������ �Ʒ�
		distance[3] = GetDistance(circleCenter.x, circleCenter.y,
			rect->right, rect->bottom);
		for (int i = 0; i < 4; i++) {
			if (distance[i] < radius)
				return true;
		}
	}

	return false;
}
