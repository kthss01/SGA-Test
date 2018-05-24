#pragma once

#include "../Common/Transform.h"
#include "../Physics/RectCollider.h"
#include "../Physics/CircleCollider.h"

class GameObject
{
protected:
	class Transform* transform;
	//class RectCollider* collider;
	class CircleCollider* collider;

	int stride;	// �� ������
	DWORD FVF;

	LPDIRECT3DVERTEXBUFFER9 vb;
	LPDIRECT3DINDEXBUFFER9 ib;
public:
	GameObject();
	~GameObject();

	virtual void Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	Transform * GetTransform() { return transform; }
};

