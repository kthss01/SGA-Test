// Day21.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Day21.h"
#include <stdio.h>

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DAY21, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DAY21));

    MSG msg;

    // 기본 메시지 루프입니다.
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DAY21));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_DAY21);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
//int num = 0;

// left top right bottom 순
RECT rc = { 100,100,200,200 };
POINT ptMouse = { 0,0 };

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// 메시지 창 안에서는 마우스 누르고 잇는 동안은 없다고 함

	char str[128];

	// static 정적, 전역 변수와 비슷한 용도로 사용한다고만 알자
	static int num = 0;	

    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다.
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다.
			//// 구구단
			//for (int i = 1; i < 10; i++) {
			//	for (int j = 1; j < 10; j++) {
			//		if (num >= i) // 1, 4, 7
			//		{
			//			sprintf_s(str, "%d * %d = %d", i, j, i*j);
			//			TextOut(hdc, 100,
			//				10 + j * 20 + ((i - 1) / 3) * 200, 
			//				str, strlen(str));
			//		}
			//		if (num >= i + 1) // 2, 5, 8
			//		{
			//			sprintf_s(str, "%d * %d = %d", i + 1, j, (i + 1)*j);
			//			TextOut(hdc, 300,
			//				10 + j * 20 + ((i - 1) / 3) * 200,
			//				str, strlen(str));
			//		}
			//		if (num >= i + 2) // 3, 6, 9
			//		{
			//			sprintf_s(str, "%d * %d = %d", i + 2, j, (i + 2)*j);
			//			TextOut(hdc, 500,
			//				10 + j * 20 + ((i - 1) / 3) * 200,
			//				str, strlen(str));
			//		}
			//	}
			//}


			Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);

			RectangleMake(hdc, 200, 200, 100, 100);

			// 우리가 설정한 창크기랑 흰색 화면이 크기랑 조금 다름
			// 바 이런것까지 같이 포함된게 크기라서
			sprintf_s(str, "X : %d, Y : %d", ptMouse.x, ptMouse.y);
			TextOut(hdc, 10, 10, str, strlen(str));

            EndPaint(hWnd, &ps);
        }
        break;
	case WM_TIMER:
		// setTimer() 초기화
		// killTimer() 해제
		break;
	case WM_MOUSEMOVE:	// 마우스 움직일때 메세지 들어오는거
		ptMouse.x = LOWORD(lParam);	// 마우스의 가로 좌표
		ptMouse.y = HIWORD(lParam);	// 마우스의 세로 좌표
		InvalidateRect(hWnd, NULL, true);
		break;
	case WM_LBUTTONDOWN:
		num++;
		if (num > 9) num = 9;
		// true 이전 녀석 지울껀지, false 이전 녀석 남길껀지
		// false는 거의 않씀, 화면 지우지 않을때나 씀
		InvalidateRect(hWnd, NULL, TRUE); 
		break;
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_LEFT:	// 키보드 왼쪽 화살표
			rc.left -= 5.0f;
			rc.right -= 5.0f;
			break;
		case VK_RIGHT:	// 키보드 오른쪽 화살표
			rc.left += 5.0f;
			rc.right += 5.0f;
			break;
		default:
			break;
		}
		InvalidateRect(hWnd, NULL, TRUE);
	}
		break;
	case WM_RBUTTONDOWN:
		num--;
		if (num < 0) num = 0;
		InvalidateRect(hWnd, NULL, TRUE);
		break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

/*
	주말 과제
	Gdiplus 사각형 충돌 배웠었음
	그 방식 활용
	
	1. 사각형 안에 조그만한 사각형
	바깥쪽 사각형만 움직이게 먼저 구현(키보드 방향키로)
	조그만한 사각형 부딪치면 바깥쪽 사각형따라 움직이게 (끌려가게)

	2. 사각형 두개 하나는 조그만한 사각형 있음
	두번째 사각형에 부딪치면 조그만한 사각형 두번째 사각형으로 이동하게 만들기
	두번째 사각형이 움직이게 

	// 힌트 객체가 바뀌는게 아니라 조그만한 사각형이 누구한테 있는지로 체크

	// 이 문제는 해결 안해도 됨
	// 겹쳐있을때 

	3. 시프트 키 누르지 않고 사각형 클릭햇을때 사각형이 마우스 따라 움직이게
	
	4. 시프트 키 누르고있을 때 오른쪽 모서리 클릭하면 확대, 왼쪽 모서리쪽 축소
	// 가까운 위치로 마우스 포인터가 이동해서
	만들엇을땐 뒤집는거 한번은 됨 그 후는 어떤 처리를 안하면 
	그후 에 안먹힘
	한 줄로 만들어버리면 그 후 확대 축소 안됨 그런 문제는 있음
	-> 시프트가 아니라 오른쪽 클릭으로

*/