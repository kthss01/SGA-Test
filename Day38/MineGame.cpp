#include "stdafx.h"
#include "MineGame.h"


MineGame::MineGame()
{
}


MineGame::~MineGame()
{
}

HRESULT MineGame::Init()
{
	int i = 0;
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			// 지뢰판
			m_box[x][y].box = RectMake(
				x * WINSIZEX / WIDTH, y * WINSIZEY / HEIGHT,
				WINSIZEX / WIDTH, WINSIZEY / HEIGHT);
			m_box[x][y].idNumber = i;
			m_box[x][y].choice = false;

			m_shuffleBox[i].box = m_box[x][y].box;
			m_shuffleBox[i].idNumber = i;
			i++;

			// 색상
			m_box[x][y].purple = false;
			m_box[x][y].red = false;
			m_box[x][y].orange = false;
			m_box[x][y].yellow = false;
			m_box[x][y].green = false;
			m_box[x][y].blue = false;

		}
	}

	// 셔플
	// idNumber랑 temp만 섞음 됨
	for (int i = 0; i < 1000; i++) {
		int dest, sour, tempNum;
		RECT temp;
		dest = RND->GetFromInto(0, (WIDTH*HEIGHT) - 1);
		sour = RND->GetFromInto(0, (WIDTH*HEIGHT) - 1);

		temp = m_shuffleBox[dest].box;
		m_shuffleBox[dest].box = m_shuffleBox[sour].box;
		m_shuffleBox[sour].box = temp;

		tempNum = m_shuffleBox[dest].idNumber;
		m_shuffleBox[dest].idNumber = m_shuffleBox[sour].idNumber;
		m_shuffleBox[sour].idNumber = tempNum;
	}

	// 지뢰
	for (int i = 0; i < MINE; i++) {
		m_mine[i].mine = m_shuffleBox[i].box;
		m_mine[i].idNumber = m_shuffleBox[i].idNumber;
		m_mine[i].stop = false;
	}

	m_win = false;
	m_lose = false;
	m_count = 0;

	return S_OK;
}

void MineGame::Release()
{
}

void MineGame::Update()
{
	m_color = 0;
	if (INPUT->GetKeyDown(VK_LBUTTON) 
		&& m_lose == false && m_win == false) {
		for (int y = 0; y < HEIGHT; y++) {
			for (int x = 0; x < WIDTH; x++) {
				if (PtInRect(&m_box[x][y].box, g_ptMouse) 
					&& m_box[x][y].choice == false) {
					m_box[x][y].choice = true;
					m_count++;	// 클릭한 횟수 설정 빈칸 다 클릭하면 게임 끝나게
					m_downX = x;
					m_downY = y;

					MineCheck(m_downX, m_downY);

					// 색상 검사
					if (m_color >= 5) m_box[x][y].purple = true;
					if (m_color == 4) m_box[x][y].red = true;
					if (m_color == 3) m_box[x][y].orange = true;
					if (m_color == 2) m_box[x][y].yellow = true;
					if (m_color == 1) m_box[x][y].green = true;
					if (m_color == 0) m_box[x][y].blue = true;	// 빈칸이면
				}
			}
		}
	}

	if (m_win == true) {
		SCENE->ChangeScene("MineWin");
	}
	if (m_lose == true) {
		SCENE->ChangeScene("MineLose");
	}
}

void MineGame::Render()
{
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			BeginSolidColor(GetMemDC(), &m_brush, RGB(255, 255, 255));
			RectangleMake(GetMemDC(), m_box[x][y].box);
			DeleteObject(m_brush);

			for (int i = 0; i < MINE; i++) {
				// 지뢰 클릭시
				if (m_mine[i].stop == true)
				{
					BeginSolidColor(GetMemDC(), &m_brush, RGB(255, 255, 255));
					RectangleMake(GetMemDC(), m_mine[i].mine);
					DeleteObject(m_brush);

					BeginSolidColor(GetMemDC(), &m_brush, RGB(0, 0, 0));
					Ellipse(GetMemDC(),
						m_mine[i].mine.left,
						m_mine[i].mine.top,
						m_mine[i].mine.right,
						m_mine[i].mine.bottom);
					DeleteObject(m_brush);
				}

				if (m_box[x][y].choice == true) {
					if (m_box[x][y].purple == true) {
						BeginSolidColor(GetMemDC(), &m_brush, RGB(128, 0, 255));
						RectangleMake(GetMemDC(), m_box[x][y].box);
						DeleteObject(m_brush);
					}
					if (m_box[x][y].red == true) {
						BeginSolidColor(GetMemDC(), &m_brush, RGB(255, 0, 0));
						RectangleMake(GetMemDC(), m_box[x][y].box);
						DeleteObject(m_brush);
					}
					if (m_box[x][y].orange == true) {
						BeginSolidColor(GetMemDC(), &m_brush, RGB(255, 128, 0));
						RectangleMake(GetMemDC(), m_box[x][y].box);
						DeleteObject(m_brush);
					}
					if (m_box[x][y].yellow == true) {
						BeginSolidColor(GetMemDC(), &m_brush, RGB(255, 255, 0));
						RectangleMake(GetMemDC(), m_box[x][y].box);
						DeleteObject(m_brush);
					}
					if (m_box[x][y].green == true) {
						BeginSolidColor(GetMemDC(), &m_brush, RGB(0, 255, 0));
						RectangleMake(GetMemDC(), m_box[x][y].box);
						DeleteObject(m_brush);
					}
					if (m_box[x][y].blue == true) {
						BeginSolidColor(GetMemDC(), &m_brush, RGB(0, 0, 255));
						RectangleMake(GetMemDC(), m_box[x][y].box);
						DeleteObject(m_brush);
					}
				}
			}
		}
	}
}

void MineGame::MineCheck(int destX, int destY)
{
	for (int i = 0; i < MINE; i++)
	{
		if (m_box[destX][destY].idNumber == m_mine[i].idNumber)
		{
			for (int i = 0; i < MINE; i++)
			{
				m_mine[i].stop = true;
				m_lose = true;
			}
		}
		else
		{
			// 왼쪽 모서리
			if (destX == 0 && destY == 0)
			{
				// 오른쪽 아래
				m_color += (m_box[destX + 1][destY + 1].idNumber == m_mine[i].idNumber) ? 1 : 0;
				// 오른쪽
				m_color += (m_box[destX + 1][destY].idNumber == m_mine[i].idNumber) ? 1 : 0;
				// 아래
				m_color += (m_box[destX][destY + 1].idNumber == m_mine[i].idNumber) ? 1 : 0;

			}

			// 왼쪽 아래 (모서리)
			else if (destX == 0 && destY == HEIGHT - 1)
			{
				// 오른쪽 위
				m_color += (m_box[destX + 1][destY - 1].idNumber == m_mine[i].idNumber) ? 1 : 0;
				// 오른쪽
				m_color += (m_box[destX + 1][destY].idNumber == m_mine[i].idNumber) ? 1 : 0;
				// 위
				m_color += (m_box[destX][destY - 1].idNumber == m_mine[i].idNumber) ? 1 : 0;
			}

			// 오른쪽위 (모서리)
			else if (destX == WIDTH - 1 && destY == 0)
			{
				// 왼쪽 아래
				m_color += (m_box[destX - 1][destY + 1].idNumber == m_mine[i].idNumber) ? 1 : 0;
				// 왼쪽
				m_color += (m_box[destX - 1][destY].idNumber == m_mine[i].idNumber) ? 1 : 0;
				// 아래
				m_color += (m_box[destX][destY + 1].idNumber == m_mine[i].idNumber) ? 1 : 0;
			}

			// 오른쪽 아래 (모서리)
			else if (destX == WIDTH - 1 && destY == HEIGHT - 1)
			{
				// 왼쪽 위
				m_color += (m_box[destX - 1][destY - 1].idNumber == m_mine[i].idNumber) ? 1 : 0;
				// 왼쪽
				m_color += (m_box[destX - 1][destY].idNumber == m_mine[i].idNumber) ? 1 : 0;
				// 위
				m_color += (m_box[destX][destY - 1].idNumber == m_mine[i].idNumber) ? 1 : 0;
			}

			// 왼쪽면
			else if (destX == 0)
			{
				// 위
				m_color += (m_box[destX][destY - 1].idNumber == m_mine[i].idNumber) ? 1 : 0;
				// 오른쪽 위
				m_color += (m_box[destX + 1][destY - 1].idNumber == m_mine[i].idNumber) ? 1 : 0;
				// 오른쪽
				m_color += (m_box[destX + 1][destY].idNumber == m_mine[i].idNumber) ? 1 : 0;
				// 오른쪽 아래
				m_color += (m_box[destX + 1][destY + 1].idNumber == m_mine[i].idNumber) ? 1 : 0;
				// 아래
				m_color += (m_box[destX][destY + 1].idNumber == m_mine[i].idNumber) ? 1 : 0;
			}
			// 오른쪽 면
			else if (destX == WIDTH - 1)
			{
				// 위
				m_color += (m_box[destX][destY - 1].idNumber == m_mine[i].idNumber) ? 1 : 0;
				// 왼쪽 위
				m_color += (m_box[destX - 1][destY - 1].idNumber == m_mine[i].idNumber) ? 1 : 0;
				// 왼쪽				  
				m_color += (m_box[destX - 1][destY].idNumber == m_mine[i].idNumber) ? 1 : 0;
				// 왼쪽 아래				 
				m_color += (m_box[destX - 1][destY + 1].idNumber == m_mine[i].idNumber) ? 1 : 0;
				// 아래
				m_color += (m_box[destX][destY + 1].idNumber == m_mine[i].idNumber) ? 1 : 0;
			}
			// 윗면
			else if (destY == 0)
			{
				// 왼쪽
				m_color += (m_box[destX - 1][destY].idNumber == m_mine[i].idNumber) ? 1 : 0;
				// 왼쪽 아래
				m_color += (m_box[destX - 1][destY + 1].idNumber == m_mine[i].idNumber) ? 1 : 0;
				// 아래
				m_color += (m_box[destX][destY + 1].idNumber == m_mine[i].idNumber) ? 1 : 0;
				// 오른쪽 아래
				m_color += (m_box[destX + 1][destY + 1].idNumber == m_mine[i].idNumber) ? 1 : 0;
				// 오른쪽
				m_color += (m_box[destX + 1][destY].idNumber == m_mine[i].idNumber) ? 1 : 0;
			}
			// 아랫면
			else if (destY == HEIGHT - 1)
			{
				// 왼쪽
				m_color += (m_box[destX - 1][destY].idNumber == m_mine[i].idNumber) ? 1 : 0;
				// 왼쪽 위
				m_color += (m_box[destX - 1][destY - 1].idNumber == m_mine[i].idNumber) ? 1 : 0;
				// 위
				m_color += (m_box[destX][destY - 1].idNumber == m_mine[i].idNumber) ? 1 : 0;
				// 오른쪽 위
				m_color += (m_box[destX + 1][destY - 1].idNumber == m_mine[i].idNumber) ? 1 : 0;
				// 오른쪽
				m_color += (m_box[destX + 1][destY].idNumber == m_mine[i].idNumber) ? 1 : 0;
			}
			// 8방향 검사
			else
			{
				// 왼쪽
				m_color += (m_box[destX - 1][destY].idNumber == m_mine[i].idNumber) ? 1 : 0;
				// 왼쪽 위
				m_color += (m_box[destX - 1][destY - 1].idNumber == m_mine[i].idNumber) ? 1 : 0;
				// 위
				m_color += (m_box[destX][destY - 1].idNumber == m_mine[i].idNumber) ? 1 : 0;
				// 오른쪽 위
				m_color += (m_box[destX + 1][destY - 1].idNumber == m_mine[i].idNumber) ? 1 : 0;
				// 오른쪽
				m_color += (m_box[destX + 1][destY].idNumber == m_mine[i].idNumber) ? 1 : 0;
				// 오른쪽 아래
				m_color += (m_box[destX + 1][destY + 1].idNumber == m_mine[i].idNumber) ? 1 : 0;
				// 아래
				m_color += (m_box[destX][destY + 1].idNumber == m_mine[i].idNumber) ? 1 : 0;
				// 왼쪽 아래
				m_color += (m_box[destX - 1][destY + 1].idNumber == m_mine[i].idNumber) ? 1 : 0;
			}
		}
	}
}
