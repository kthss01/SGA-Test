#include "stdafx.h"
#include "Util.h"

namespace Util {
	LPDIRECT3DDEVICE9 Device;

	void CreateDevice()
	{
		//
		//	Direct3D 초기화
		//

		/// 1. Device를 생성할 IDirect3D9 객체를 얻는다.
		//IDirect3D9* d3d9; // 다이렉트는 포인터면 보통 LP로 만들어둠
		LPDIRECT3D9 d3d9;
		d3d9 = Direct3DCreate9(D3D_SDK_VERSION);

		// IDirect3D9 객체 초기화 실패시 NULL 반환이 됨
		if (d3d9 == NULL) {
			// MessageBox에 NULL을 붙일 수도 있음 (handle 값 넣는대신 (hwnd))
			// NULL로 하면 창꺼질 때 같이 안꺼진다는 차이정도
			MessageBox(NULL,
				L"Direct3DCreate9() - FAILED",
				L"FAILED", MB_OK);
			// assert는 안이 true면 패스 false면 종료함
			assert(false);
		}

		/// 2. 하드웨어 정보를 가지고 와서
		// 정점 프로세스 타입 지정
		// 하드웨어 정보 - 그래픽 카드 정보라고 보면됨
		D3DCAPS9 caps;

		d3d9->GetDeviceCaps(
			D3DADAPTER_DEFAULT, // 주로 사용하는 그래픽의 값
			D3DDEVTYPE_HAL, // 디바이스 타입
			&caps
		);

		// 정점 계산 처리 방식
		// 정점 처리 방식을 그래픽 카드에서 할꺼냐 하드웨어에서 할꺼냐
		DWORD vertexProcessing;

		if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
			vertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;
		else
			vertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

		// D3DPRESENT_PARAMETERS 구조체 정보 생성
		// 이 정보로 Device를 만들게 됨

		D3DPRESENT_PARAMETERS d3dpp;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8; // 4바이트로 만드는거 24비트 8비트
		// 백버퍼 갯수 여러개 있어도 상관 없음
		// 백버퍼 여러개 있으면 부분 부분으로 렌더할 때 좋음
		d3dpp.BackBufferCount = 1; 
		d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8; // 총 4바이트 색상값 설정
		d3dpp.BackBufferHeight = WINSIZE_Y;
		d3dpp.BackBufferWidth = WINSIZE_X;
		// true로 쓰면 3D가 되고 false으면 애매한 2D가 됨
		// 멀리있는건 가까이있건 크기가 같아야되는데 멀어지면 작아짐
		d3dpp.EnableAutoDepthStencil = true; 

		// 다른 옵션
		d3dpp.Flags = 0;
		// 전체화면 상태일 때 주사율 어떻게 설정할 건지
		// 주사율 좋을 수록 잘 보임
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		// 화면에 출력할 윈도우
		d3dpp.hDeviceWindow = g_hWnd;
		// Sample 텍스처 어떻게 처리할 것이냐
		// 여러 장의 텍스처 설정할 때 퀄리티 어떻게 할 것이냐
		d3dpp.MultiSampleQuality = 0; // 따로 설정 안한다는 얘기
		// 안티 앨리어싱 사용하지 않겠다.
		// 그래픽 품질 향상 기술
		d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
		// 화면 전송 간격
		// d3dpp.FullScreen_RefresuhRateInHz와 같은건데 전체화면이 아닐때 설정
		// ONE이라는 것은 주모니터 화면과 같은 주사율로 출력하겠다는 거
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
		// 화면 전환할 때 쓰는걸 swap effect
		// 화면 전환을 할 때 데이터를 어떻게 쓸 것이냐
		// discard 전환할때 데이터 저장하지 않겠다는거
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		// 창으로 띄우겠느냐
		d3dpp.Windowed = true;

		/// 3. Device 생성
	
		HRESULT hr = d3d9->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			g_hWnd,
			vertexProcessing,
			&d3dpp,
			&Device
		);

		// hr이 실패했으면 true, 성공했으면 false (FAILED는)
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