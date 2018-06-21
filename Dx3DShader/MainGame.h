#pragma once
class MainGame {
private:
	LPD3DXMESH pMeshSphere;
	LPD3DXEFFECT pSkyDomeEffect;

	LPD3DXEFFECT pLightShader;
	D3DXVECTOR3 vLightDir; // 라이트에 대한 방향값

	float fAngleX, fAngleY;
public:
	MainGame();
	~MainGame();

	void Init();
	void Release();
	void Update();
	void Render();
};