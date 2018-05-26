#pragma once

// MainGame대신 돌아갈꺼

class Program
{
private:
	// 기본적으로 도형 만들려면 vertex 필요
	struct Vertex {
		Vector2 position;
		DWORD color;
	};

	Vertex* vertices;
	Matrix matView;
	Matrix matProjection;
	// viewPort 필요없음 
	// 윈도우 쓰겠다고 선언된 순간부터 window 기준으로 되어있음
	Vector2 vEye;
	Vector2 outPos;

	Ray ray;

	float color[4];

	class Rect* head;
	class Rect* body;
	class Rect* lArm;
	class Rect* rArm;
	class Rect* lLeg;
	class Rect* rLeg;

	// 텍스에 대한 정보를 저장할 곳
	LPDIRECT3DTEXTURE9 pRenderTexture;
	// 텍스에 대한 표면 (색상값 설정)
	LPDIRECT3DSURFACE9 pRenderSurface;

	vector< pair<LPDIRECT3DTEXTURE9, D3DXIMAGE_INFO> > vecImage;

	class Camera* mainCamera;

	Vector2 mousePosWithScreen;
	float radius;
	bool isCheck;

	LPDIRECT3DTEXTURE9 texture;
	LPDIRECT3DTEXTURE9 tempTex;

	LPD3DXSPRITE sprite;
public:
	Program();
	~Program();

	void Update();
	void Render();

	void CreateRenderTargetTexture();
};

/*
	과제1
	텍스처 읽어와서 픽셀 단위로 체크해서 배경색이 아닌거 윈도우 화면에 출력

	과제2
	하늘에서 사각형 뿌림 랜덤한 크기 방향 회전 해서 떨어짐
	쌓여야함 회전한 방향이면 그방향으로 떨어져야함
	바닥에 닿거나 다른녀석에 닿으면 멈추게끔
	공중에서는 영향 안받으면됨
	멈춰잇는 애들만 충돌하게끔
*/