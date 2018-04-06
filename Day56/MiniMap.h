#pragma once

#include "GameNode.h"

// �̴ϸ��� �ܼ��� ���� �ʿ��� �������� ����Ѵٰ� �����ϸ��
/*
	ȭ����ü�� 1 / 10 ���� �ٿ���
*/

enum playerState {
	PS_IDLE,
	PS_RUN
};

class MiniMap : public GameNode
{
private:
	Image * _megaman;
	int _alpha;
	int _camera;	// ĳ���� �����̸� ī�޶��� ��ġ �ٲ��ٲ�
	int _index;	// �ִϸ��̼� �������� ���� �༮
	bool _isLeft;
	playerState _ps;
public:
	MiniMap();
	~MiniMap();

	HRESULT Init();
	void Release();
	void Update();
	void Render();
};

