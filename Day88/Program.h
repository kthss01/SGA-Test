#pragma once

// MainGame대신 돌아갈꺼

class Program
{
private:
	// 기본적으로 도형 만들려면 vertex 필요
	struct Vertex {
		Vector2 position;
		float size;	// 정점이 가지는 사이즈
		//Vector2 uv;
		DWORD color;

		// PSIZE = point size
		enum { FVF = D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_DIFFUSE };
	};

private:
	Vertex vertices[100];
	LPDIRECT3DTEXTURE9 pTex;

	class Camera* mainCamera;
public:
	Program();
	~Program();

	void Update();
	void Render();
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