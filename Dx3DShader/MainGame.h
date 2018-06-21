#pragma once
class MainGame {
private:
	LPD3DXMESH pMeshSphere;
	LPD3DXEFFECT pSkyDomeEffect;

	LPD3DXEFFECT pLightShader;
	D3DXVECTOR3 vLightDir; // ����Ʈ�� ���� ���Ⱚ

	float fAngleX, fAngleY;
public:
	MainGame();
	~MainGame();

	void Init();
	void Release();
	void Update();
	void Render();
};