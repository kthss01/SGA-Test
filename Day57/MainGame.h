#pragma once

#include "GameNode.h"

// ����â�� ����µ� �ʿ��� ���
#include <commdlg.h>

class MainGame : public GameNode
{
private:
	bool isDebug;

	struct RenderImage{
		POINT position;
		POINT frame;
	};

	vector<RenderImage> images;

	Image * bg;

	OPENFILENAME OFN;
	char filePath[MAX_PATH];	// �ִ� ��� ����
public:
	MainGame();
	~MainGame();

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};
