#pragma once
class D2D
{
private:
	LPDIRECT3D9 d3d; //컴퓨터의 사양을 
	static LPDIRECT3DDEVICE9 device;

	static D2D* instance;

	D2D();
	~D2D();
public:
	static D2D* Get();
	static void Delete();

	static LPDIRECT3DDEVICE9 GetDevice()
	{
		return device;
	}
	
	void BeginScene(DWORD color);
	void EndScene();
};

