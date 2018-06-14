#include "stdafx.h"
#include "Util.h"

namespace Util {
	LPDIRECT3DDEVICE9 Device;

	void CreateDevice()
	{
		//
		//	Direct3D �ʱ�ȭ
		//

		/// 1. Device�� ������ IDirect3D9 ��ü�� ��´�.
		//IDirect3D9* d3d9; // ���̷�Ʈ�� �����͸� ���� LP�� ������
		LPDIRECT3D9 d3d9;
		d3d9 = Direct3DCreate9(D3D_SDK_VERSION);

		// IDirect3D9 ��ü �ʱ�ȭ ���н� NULL ��ȯ�� ��
		if (d3d9 == NULL) {
			// MessageBox�� NULL�� ���� ���� ���� (handle �� �ִ´�� (hwnd))
			// NULL�� �ϸ� â���� �� ���� �Ȳ����ٴ� ��������
			MessageBox(NULL,
				L"Direct3DCreate9() - FAILED",
				L"FAILED", MB_OK);
			// assert�� ���� true�� �н� false�� ������
			assert(false);
		}

		/// 2. �ϵ���� ������ ������ �ͼ�
		// ���� ���μ��� Ÿ�� ����
		// �ϵ���� ���� - �׷��� ī�� ������� �����
		D3DCAPS9 caps;

		d3d9->GetDeviceCaps(
			D3DADAPTER_DEFAULT, // �ַ� ����ϴ� �׷����� ��
			D3DDEVTYPE_HAL, // ����̽� Ÿ��
			&caps
		);

		// ���� ��� ó�� ���
		// ���� ó�� ����� �׷��� ī�忡�� �Ҳ��� �ϵ����� �Ҳ���
		DWORD vertexProcessing;

		if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
			vertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;
		else
			vertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

		// D3DPRESENT_PARAMETERS ����ü ���� ����
		// �� ������ Device�� ����� ��

		D3DPRESENT_PARAMETERS d3dpp;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8; // 4����Ʈ�� ����°� 24��Ʈ 8��Ʈ
		// ����� ���� ������ �־ ��� ����
		// ����� ������ ������ �κ� �κ����� ������ �� ����
		d3dpp.BackBufferCount = 1; 
		d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8; // �� 4����Ʈ ���� ����
		d3dpp.BackBufferHeight = WINSIZE_Y;
		d3dpp.BackBufferWidth = WINSIZE_X;
		// true�� ���� 3D�� �ǰ� false���� �ָ��� 2D�� ��
		// �ָ��ִ°� �������ְ� ũ�Ⱑ ���ƾߵǴµ� �־����� �۾���
		d3dpp.EnableAutoDepthStencil = true; 

		// �ٸ� �ɼ�
		d3dpp.Flags = 0;
		// ��üȭ�� ������ �� �ֻ��� ��� ������ ����
		// �ֻ��� ���� ���� �� ����
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		// ȭ�鿡 ����� ������
		d3dpp.hDeviceWindow = g_hWnd;
		// Sample �ؽ�ó ��� ó���� ���̳�
		// ���� ���� �ؽ�ó ������ �� ����Ƽ ��� �� ���̳�
		d3dpp.MultiSampleQuality = 0; // ���� ���� ���Ѵٴ� ���
		// ��Ƽ �ٸ���� ������� �ʰڴ�.
		// �׷��� ǰ�� ��� ���
		d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
		// ȭ�� ���� ����
		// d3dpp.FullScreen_RefresuhRateInHz�� �����ǵ� ��üȭ���� �ƴҶ� ����
		// ONE�̶�� ���� �ָ���� ȭ��� ���� �ֻ����� ����ϰڴٴ� ��
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
		// ȭ�� ��ȯ�� �� ���°� swap effect
		// ȭ�� ��ȯ�� �� �� �����͸� ��� �� ���̳�
		// discard ��ȯ�Ҷ� ������ �������� �ʰڴٴ°�
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		// â���� ���ڴ���
		d3dpp.Windowed = true;

		/// 3. Device ����
	
		HRESULT hr = d3d9->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			g_hWnd,
			vertexProcessing,
			&d3dpp,
			&Device
		);

		// hr�� ���������� true, ���������� false (FAILED��)
		if (FAILED(hr)) {
			d3d9->Release();
			d3d9 = 0;

			MessageBox(NULL,
				L"CreateDevice() - FAILED",
				L"FAILED", MB_OK);
			assert(SUCCEEDED(hr));
		}

		d3d9->Release();
		d3d9 = 0;
	}

	void ReleaseDevice()
	{
		if (Device) {
			Device->Release();
			Device = 0;
		}
	}
}