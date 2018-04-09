#pragma once

#include "GameNode.h"

// 선택창을 만드는데 필요한 헤더
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
	char filePath[MAX_PATH];	// 최대 경로 길이
public:
	MainGame();
	~MainGame();

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};
