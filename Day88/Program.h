#pragma once

// MainGame대신 돌아갈꺼

class Program
{
//private:
//	// 기본적으로 도형 만들려면 vertex 필요
//	struct Vertex {
//		Vector2 position;
//		float size;	// 정점이 가지는 사이즈
//		//Vector2 uv;
//		DWORD color;
//
//		// PSIZE = point size
//		enum { FVF = D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_DIFFUSE };
//	};
//
//private:
//	Vertex vertices[100];
//	LPDIRECT3DTEXTURE9 pTex;

private:

	LPDIRECT3DTEXTURE9 pTex;

	class ParticleEmitter* particle;
	class Camera* mainCamera;
public:
	Program();
	~Program();

	void Update();
	void Render();
};

/*
	과제1 
	스택 구현

	과제2
	중위 표기법 -> 후기 표기법으로 변경 (스택 이용)

	과제3 
	후위 표기법 스택으로 계산해 오기

	중위 표기법
	ex) 2 + 3 * (5 + 4 * 2) - 3 + 6

	후위 표기법 
	23542*+*+3-6+

	(4 * 2 + 5) * 3 + 2 - 3 + 6
	
	스택 (자료 구조) 계산기 만들어 오기

	과제
	중위 표기법 받아서
	후위 표기법으로 변경후 결과값 출력하기
*/