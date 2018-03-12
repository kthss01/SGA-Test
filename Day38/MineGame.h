#pragma once

#include "GameNode.h"

#define WIDTH 20	// rect �ʺ� �׳� ������ ���� row
#define HEIGHT 20	// rect ���� �׳� ������ ���� col
#define MINE 80		// ���� ����

struct tagPuzzle {
	RECT box;		// ���ڰ� �ִ��� ���������� ��ġ�� Rect
	bool choice;
	bool flag;

	// ���ڵ� idNumber ���� �ְ� puzzle�� ���ؼ� ���� �ִ��� Ȯ��
	int idNumber;	

	// �ֺ��� �ִ� ���� ���� ���� enum���� �ص� ��
	bool purple;
	bool red;
	bool orange;
	bool yellow;
	bool green;
	bool blue;
};

struct tagLandMine {
	RECT mine;
	bool stop;	// mine�� ���������� �����ؾߵǱ� ������
	int idNumber;
};

class MineGame : public GameNode
{
private:
	tagPuzzle m_box[WIDTH][HEIGHT];
	tagPuzzle m_shuffleBox[WIDTH * HEIGHT];
	tagLandMine m_mine[MINE];

	HBRUSH m_brush;
	int m_downX, m_downY;	// ���� ���� Ŭ���� �༮�� ��ȣ

	bool m_win, m_lose;		// �̰�� ���Ŀ� ���� �� �����ϸ� ��
	char m_winner[64];
	int m_color;			// ��� ���� ���� �ٲܰ�
	int m_count;			// color�� ����� �뵵

public:
	MineGame();
	~MineGame();

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	// destX, destY, downX, downY ����
	void MineCheck(int destX, int destY);
};

