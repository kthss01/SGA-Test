#pragma once

#include "GameNode.h"
#include "Object.h"

class MainGame : public GameNode
{
private:
	bool isDebug;

	Object* object[10];

	int removeObject; // removeObject 이용해서 임의적으로 삭제할꺼
public:
	MainGame();
	~MainGame();

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};
