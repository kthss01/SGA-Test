#include "stdafx.h"
#include "Omok.h"


Omok::Omok()
{
}


Omok::~Omok()
{
}

HRESULT Omok::Init()
{
	m_turn = 0;
	m_gameOver = false;

	int tempWidth = WINSIZEX / 20;
	int tempHeight = WINSIZEY / 20;

	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++) {
			m_loc[i][j].loc = NONE;
			m_loc[i][j].x = (j + 1) * tempWidth;
			m_loc[i][j].y = (i + 1) * tempHeight;
			m_loc[i][j].rc = RectMakeCenter(
				m_loc[i][j].x, m_loc[i][j].y, tempWidth, tempHeight);
		}
	}

	m_bg = new Image;
	m_bg->Init("images/bg.bmp", WINSIZEX, WINSIZEY);
	m_locImage[0] = new Image;
	m_locImage[0]->Init("images/black.bmp", WINSIZEX / 20, WINSIZEY / 20, true);
	m_locImage[1] = new Image;
	m_locImage[1]->Init("images/white.bmp", WINSIZEX / 20, WINSIZEY / 20, true);

	m_isDebug = false;

	return S_OK;
}

void Omok::Release()
{
	SAFE_DELETE(m_bg);
	SAFE_DELETE(m_locImage[0]);
	SAFE_DELETE(m_locImage[1]);
}

void Omok::Update()
{
	if (INPUT->GetKeyDown(VK_LBUTTON) && m_gameOver == false) {
		for (int i = 0; i < 19; i++) {
			for (int j = 0; j < 19; j++) {
				if (PtInRect(&m_loc[i][j].rc, g_ptMouse)
					&& m_loc[i][j].loc == NONE) {
					m_loc[i][j].loc = (m_turn % 2 == 0) ? BLACK : WHITE;

					m_turn++;
				}
			}
		}
	}

	// �˻�
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			// ���� �� 5���� üũ�ϸ� ��

			// �� ���
			// ����
			if (m_loc[i][j + 0].loc == WHITE &&
				m_loc[i][j + 1].loc == WHITE &&
				m_loc[i][j + 2].loc == WHITE &&
				m_loc[i][j + 3].loc == WHITE &&
				m_loc[i][j + 4].loc == WHITE) {
				m_gameOver = true;
				m_wp = WP_WHITE;
			}
			// ����
			if (m_loc[i + 0][j].loc == WHITE &&
				m_loc[i + 1][j].loc == WHITE &&
				m_loc[i + 2][j].loc == WHITE &&
				m_loc[i + 3][j].loc == WHITE &&
				m_loc[i + 4][j].loc == WHITE) {
				m_gameOver = true;
				m_wp = WP_WHITE;
			}
			// ���� �밢��
			if (i > 3 &&
				m_loc[i - 0][j + 0].loc == WHITE &&
				m_loc[i - 1][j + 1].loc == WHITE &&
				m_loc[i - 2][j + 2].loc == WHITE &&
				m_loc[i - 3][j + 3].loc == WHITE &&
				m_loc[i - 4][j + 4].loc == WHITE
				) {
				m_gameOver = true;
				m_wp = WP_WHITE;
			}
			// ���� �밢��
			if (i > 3 &&
				m_loc[i + 0][j + 0].loc == WHITE &&
				m_loc[i + 1][j + 1].loc == WHITE &&
				m_loc[i + 2][j + 2].loc == WHITE &&
				m_loc[i + 3][j + 3].loc == WHITE &&
				m_loc[i + 4][j + 4].loc == WHITE
				) {
				m_gameOver = true;
				m_wp = WP_WHITE;
			}

			// ���� �巡�״� alt ������ �巡�� �ϸ��
			// �浹 ���
			// ����
			if (m_loc[i][j + 0].loc == BLACK &&
				m_loc[i][j + 1].loc == BLACK &&
				m_loc[i][j + 2].loc == BLACK &&
				m_loc[i][j + 3].loc == BLACK &&
				m_loc[i][j + 4].loc == BLACK) {
				m_gameOver = true;
				m_wp = WP_BLACK;
			}
			// ����
			if (m_loc[i + 0][j].loc == BLACK &&
				m_loc[i + 1][j].loc == BLACK &&
				m_loc[i + 2][j].loc == BLACK &&
				m_loc[i + 3][j].loc == BLACK &&
				m_loc[i + 4][j].loc == BLACK) {
				m_gameOver = true;
				m_wp = WP_BLACK;
			}
			// ���� �밢��
			if (i > 3 &&
				m_loc[i - 0][j + 0].loc == BLACK &&
				m_loc[i - 1][j + 1].loc == BLACK &&
				m_loc[i - 2][j + 2].loc == BLACK &&
				m_loc[i - 3][j + 3].loc == BLACK &&
				m_loc[i - 4][j + 4].loc == BLACK
				) {
				m_gameOver = true;
				m_wp = WP_BLACK;
			}
			// ���� �밢��
			if (i > 3 &&
				m_loc[i + 0][j + 0].loc == BLACK &&
				m_loc[i + 1][j + 1].loc == BLACK &&
				m_loc[i + 2][j + 2].loc == BLACK &&
				m_loc[i + 3][j + 3].loc == BLACK &&
				m_loc[i + 4][j + 4].loc == BLACK
				) {
				m_gameOver = true;
				m_wp = WP_BLACK;
			}
		}
	}

	if (INPUT->GetKeyDown(VK_F11)) {
		m_isDebug = !m_isDebug;
	}
}

void Omok::Render()
{
	m_bg->Render(GetMemDC());

	char tempChar[128];
	if (m_turn % 2 == 0)
		sprintf_s(tempChar, "�浹 ����");
	if (m_turn % 2 == 1)
		sprintf_s(tempChar, "�鵹 ����");

	if (m_gameOver == true && m_wp == WP_WHITE) {
		sprintf_s(tempChar, "�鵹 �¸�");
	}
	if (m_gameOver == true && m_wp == WP_BLACK) {
		sprintf_s(tempChar, "�浹 �¸�");
	}

	// �ؽ�ó ���� �ɼ� ���� �⺻�� ���� ����
	SetTextAlign(GetMemDC(), TA_CENTER);
	// ���ڻ��� ���ȭ�� ����
	SetBkMode(GetMemDC(), TRANSPARENT); // �����ϰ�
	TextOut(GetMemDC(), WINSIZEX / 2, 0, tempChar, strlen(tempChar));

	// ���� �׸���
	for (int i = 0; i < 19; i++) {
		LineMake(GetMemDC(), m_loc[i][0].x, m_loc[i][0].y, 
			m_loc[i][18].x, m_loc[i][18].y);
		LineMake(GetMemDC(), m_loc[0][i].x, m_loc[0][i].y,
			m_loc[18][i].x, m_loc[18][i].y);
	}

	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++) {
			if (m_loc[i][j].loc == WHITE) {
				m_locImage[1]->Render(GetMemDC(),
					m_loc[i][j].rc.left, m_loc[i][j].rc.top);
			}
			if (m_loc[i][j].loc == BLACK) {
				m_locImage[0]->Render(GetMemDC(),
					m_loc[i][j].rc.left, m_loc[i][j].rc.top);
			}

			if (m_isDebug) {
				RectangleMake(GetMemDC(), m_loc[i][j].rc);
			}
		}
	}
}
