#include "stdafx.h"
#include "MainGame6.h"


MainGame6::MainGame6()
{
}


MainGame6::~MainGame6()
{
}

HRESULT MainGame6::Init()		// �ʱ�ȭ
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
		// ȭ�� ������ ������ �ʰ� ����
		m_bullet[i].x = RND->GetFromInto(10, WINSIZEX - 10);
		m_bullet[i].y = RND->GetFromInto(-600, 0);
		m_bullet[i].speed = RND->GetFromInto(3, 6);
		m_bullet[i].rc = RectMakeCenter(m_bullet[i].x, m_bullet[i].y, 10, 10);
	}
	
	m_score = 0;

	return S_OK;
}

void MainGame6::Release()		// �̹����� ����ϱ� �������� ������ ���� ����
{
	GameNode::Release();
}

void MainGame6::Update()		// Ű���峪 ���콺 ó��, �ڵ������� �ؾ��� �� ó��
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
	//// Ư�� �༮ (����Ű ������) ���� ���ڸ� Ȯ���ϰ� ������ ���� �ֱ�
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
	//// ��ǻ�� ���ɿ� ���� �ȵǴ� ����� ����
	//count++;
	//if (count % 1000) {
	//	rc.left += 3.0f;
	//	rc.right += 3.0f;
	//	count = 0;
	//}
	//
	//// �̷��� ����ϸ� �� �˰� ���� ��
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

	// �÷��̾� �̵�
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
		// ȭ�� ������ ������ �Ǹ�
		if (m_bullet[i].rc.top > WINSIZEY) {
			m_bullet[i].y = RND->GetFromInto(-600, 0);
			m_score++;	// �� �� ���Ѱɷ� ����
		}
		RECT temp;
		if (IntersectRect(&temp, &m_bullet[i].rc, &m_player)) {
			// �浹 �� ó��

			// â ���� ������
			//PostQuitMessage(0);

			// ȭ�� ���߰� ������
			KillTimer(g_hWnd, 1);

			// �ٽ� �����ϰ� ������ 
			//Init();

			// �Ͻ����� �����ϰ� ������
			//Sleep(2000);
			//Init();
			// �Ǵ� Kill �ϰ� SetTimer �ϸ� ��
		}
	}
}

void MainGame6::Render(HDC hdc)	// ���
{
	//GameNode::Render(hdc);
	// ����ۿ� �ѷ��ش� (�������� �׳� �Ѱ�)
	HDC memDC = this->GetBackBuffer()->GetMemDC();
	// ��� �� ��Ʈ��
	// PatBlt ������ �����ִ� �Լ�
	// �ȿ� �� �༮ ������� ä��°�
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
	// render �������� brush �����ϱ� ������
	DeleteObject(brush);

	for (int i = 0; i < BULLETMAX; i++) {
		HBRUSH brush = CreateSolidBrush(RGB(r, g, b));
		// �ܰ����� ����
		// �ܰ����� �ʿ��ϸ� Rectangle�ϰ�
		FillRect(memDC, &m_bullet[i].rc, brush);
		// render �������� brush �����ϱ� ������
		DeleteObject(brush);
	}

	// ������ strScore ���� ���� Debug x64 �����̾ �׷��� 
	// �̰͸� x86�� �ٲ㵵 ���� �ذ��
	char strScore[64];
	sprintf_s(strScore, "Score : %d ", m_score);
	TextOut(memDC, 10, 10, strScore, strlen(strScore));

	//============================================================
	// ���⵵ ������ ����� �ȵ�
	this->GetBackBuffer()->Render(hdc);
}

