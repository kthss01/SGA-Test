#pragma once
#include "GameNode.h"

enum Loc {
	NONE,
	BLACK,
	WHITE
};

enum WinPlayer {
	WP_BLACK,
	WP_WHITE
};

struct tagLoc {
	Loc loc;
	RECT rc;
	float x, y;
};

class Omok : public GameNode
{
private:
	tagLoc m_loc[19][19];
	bool m_gameOver;
	WinPlayer m_wp;
	int m_turn;

	Image * m_bg;
	Image * m_locImage[2];

	bool m_isDebug;
public:
	Omok();
	~Omok();

	HRESULT Init();
	void Release();
	void Update();
	void Render();
};

