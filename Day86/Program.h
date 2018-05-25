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
	과제
	기즈모 이용해서 원 만들기
	기즈모 클래스에 Circle 이용해서
	그랑죠 이미지 세개 기즈모 그리기
*/