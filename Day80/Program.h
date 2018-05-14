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

	class Rect* rect;

	// 텍스에 대한 정보를 저장할 곳
	LPDIRECT3DTEXTURE9 pRenderTexture;
	// 텍스에 대한 표면 (색상값 설정)
	LPDIRECT3DSURFACE9 pRenderSurface;
public:
	Program();
	~Program();

	void Update();
	void Render();

	void CreateRenderTargetTexture();
};

/*
	과제
	마리오 뛰어다니고 점프하고 하는 거 구현하기
*/

/*
	과제
	1. 쉐이더 이용해서 애니메이션 
	2. BaseColor + TextureMapping 쉐이더 합쳐오기
	원본색에 텍스처 입히는 한 쉐이더에 때려박으면 될꺼 같음
	3. 미니맵
*/