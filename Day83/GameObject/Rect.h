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

	LPD3DXEFFECT pEffect;

	LPDIRECT3DTEXTURE9 pTexture;

	Transform* tempTrans[100];
public:
	Rect();
	~Rect();

	void Init(wstring shaderFile, const Vector2 uv, const Vector2 pivot = Vector2(0, 0));
	void Release();
	void Update();
	void Render(class Camera * mainCamera);
	void RenderRect();

	void SetTexture(LPDIRECT3DTEXTURE9 tex);

	void DrawInterface();
	void WriteJsonData(wstring fileName, Json::Value* root);
	void ReadJsonData(wstring fileName, Json::Value* root);
};