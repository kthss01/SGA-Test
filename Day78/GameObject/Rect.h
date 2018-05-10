#pragma once
#include "GameObject.h"
class Rect : public GameObject
{
private:
	struct Vertex {
		Vector2 position;
		Vector2 uv;
	};
	Vertex vertice[4];

	LPDIRECT3DTEXTURE9 pTex;
	float deltaTime;
public:
	Rect();
	~Rect();

	void Init();
	void Release();
	void Update();
	void Render();

	void DrawInterface();
};