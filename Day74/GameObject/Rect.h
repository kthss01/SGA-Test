#pragma once
#include "GameObject.h"
class Rect : public GameObject
{
private:
	struct Vertex {
		Vector2 position;
		DWORD color;
	};
	Vertex vertice[4];
public:
	Rect();
	~Rect();

	void Init();
	void Release();
	void Update();
	void Render();

	void DrawInterface();
};