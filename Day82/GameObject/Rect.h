#pragma once
#include "GameObject.h"
class Rect : public GameObject
{
private:
	struct Vertex {
		Vector2 position;
		//DWORD color;
		Vector2 uv;
	};
	Vertex vertice[4];

	LPDIRECT3DTEXTURE9 pTex;
	LPDIRECT3DTEXTURE9 pTex2;

	LPD3DXEFFECT pEffect;
	float deltaTime;

	class Camera* mainCamera;
	class AnimationClip* clips;

	Transform* child[4];
public:
	Rect();
	~Rect();

	void Init();
	void Release();
	void Update();
	void Render();
	void RenderRect();

	void DrawInterface();
	void WriteJsonData(wstring fileName, Json::Value* root);
	void ReadJsonData(wstring fileName, Json::Value* root);
};