#pragma once
class Program
{
private:
	
	struct Vertex
	{
		Vector2 position;
		Vector2 uv;
	};
	Vertex* vertices;

	Matrix matView;
	Matrix matProjection;

	//LPDIRECT3DVERTEXBUFFER9 tri_vb;
	LPDIRECT3DVERTEXBUFFER9 rect_vb;
	LPDIRECT3DVERTEXBUFFER9 rect4_vb;

	LPDIRECT3DTEXTURE9 texture;
public:
	Program();
	~Program();

	void Update();
	void Render();
};

