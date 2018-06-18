#pragma once
class MainGame {
private:
	LPD3DXMESH pMeshSphere;
	LPD3DXEFFECT pSkyDomeEffect;

public:
	MainGame();
	~MainGame();

	void Init();
	void Release();
	void Update();
	void Render();
};