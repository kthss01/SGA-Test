#pragma once

// MainGame대신 돌아갈꺼

class Program
{
private:
	// 기본적으로 도형 만들려면 vertex 필요
	struct Vertex {
		Vector2 position;
		Vector2 uv;	// texture 좌표
		//DWORD color;
	};

	Vertex* vertices;
	DWORD* indices;		// 인덱스 int로 해도 됨 word만 2byte이니 조심

	Matrix matView;
	Matrix matProjection;
	// viewPort 필요없음 
	// 윈도우 쓰겠다고 선언된 순간부터 window 기준으로 되어있음

	// GPU 계산을 하고 싶으면
	// Graphic 카드가 쓸 수 있도록 재포장해주는거
	// 여기 넣고나서부터는 값을 확인해 줄 수 없어서 이해가 어려움
	// 도형 하나만 들어감
	LPDIRECT3DVERTEXBUFFER9 vb;
	LPDIRECT3DINDEXBUFFER9 ib;	// 원리는 동일

	LPDIRECT3DTEXTURE9 pTex;

	Vector2 vEye;

	LPD3DXFONT font;

	Vector2 mousePos;

	bool check;

	bool subWindow;
public:
	Program();
	~Program();

	void Update();
	void Render();
};

