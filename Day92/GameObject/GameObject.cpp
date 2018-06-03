#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject()
{
	transform = new Transform;
}


GameObject::~GameObject()
{
	SAFE_DELETE(transform);
}

void GameObject::Init()
{
}

void GameObject::Release()
{
}

void GameObject::Update()
{
}

void GameObject::Render()
{
}
