#pragma once

#define WINSIZE_X 1024
#define WINSIZE_Y 768

extern HWND g_hWnd;

namespace Util {
	extern LPDIRECT3DDEVICE9 Device;

	void CreateDevice();
	void ReleaseDevice();

}