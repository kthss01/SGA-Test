#include "stdafx.h"
#include "D2D.h"

D2D* D2D::instance = NULL;
LPDIRECT3DDEVICE9 D2D::device = NULL;

D2D::D2D()
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	assert(d3d != NULL);

	D3DPRESENT_PARAMETERS param = { 0 };
	param.Windowed = TRUE;
	param.SwapEffect = D3DSWAPEFFECT_DISCARD;
	param.AutoDepthStencilFormat = D3DFMT_D16;
	param.EnableAutoDepthStencil = TRUE;

	HRESULT hr;

	hr = d3d->CreateDevice
	(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		g_hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&param,
		&device
	);
	assert(SUCCEEDED(hr) && "Not CreateDevice`");
}


D2D::~D2D()
{
	SAFE_RELEASE(device);
	SAFE_RELEASE(d3d);
}

//싱글톤처리
D2D * D2D::Get()
{
	if (instance == NULL)
		instance = new D2D;
	return instance;
}

void D2D::Delete()
{
	if (instance != NULL)
		SAFE_DELETE(instance);
}

void D2D::BeginScene(DWORD color)
{
	device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		color, 1.0f, 0.0f);
	device->BeginScene(); //후면 버퍼에 쓴다.
}

void D2D::EndScene()
{
	device->EndScene();//
	device->Present(NULL, NULL, NULL, NULL);//후면 ->전면
}
