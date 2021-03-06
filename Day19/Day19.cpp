// Day19.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Day19.h"
#include <iostream>
#include <stdio.h>

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
// HINSTANCE OS 사양 파악 윈도우 10 같은거
HWND hWnd;	// HWND Handle 내가 띄우고 있는 창들 중에서 내가 작업하고잇는 녀석 구분

WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// api main이라고 보면 됨
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,			// 이건 사용 함
                     _In_opt_ HINSTANCE hPrevInstance,	// 이건 사용 x
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DAY19, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DAY19));

    MSG msg;

    // 기본 메시지 루프입니다.
	// 키보드 나 마우스 입력했을때 대문자,소문자,숫자 그런거 인식해서
	// 마우스 클릭했는지 안했는지, 키보드 눌럿다 뗀건지 등등
	// 검사한다고 보면 됨
	// 콜백함수 호출하는 모든게 메시지라고 보면됨
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
    WNDCLASSEXW wcex;	// 윈도우 클래스의 속성 설정
	// 처음 띄우는 창이 윈도우 클래스

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DAY19));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_DAY19);
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

   // 윈도우 창 설정 createWindoW 이게
   // HWND 번호를 설정해주는거 이 창이 window 창인지
   hWnd = CreateWindowW(
	   szWindowClass,						// 윈도우 클래스 이름
	   (LPCWSTR)"1801API",					// 윈도우 타이틀 이름
	   // 그냥 하면 문자열 깨짐 프로젝트 속성에 문자집합 멀티바이트로 바꿈
	   WS_OVERLAPPEDWINDOW,					// 윈도우 스타일
	   // 모니터 기준으로 왼쪽 상단이 0,0
      0,									// 윈도우 화면의 시작 x좌표
	   0,									// 윈도우 화면의 시작 y좌표
	   1024,								// 윈도우 화면의 가로 크기
	   768,									// 윈도우 화면의 세로 크기
	   nullptr, nullptr, hInstance,			// 이 3개는 잘 안씀
	   nullptr);							// 사용하지 않음

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

// 전역변수
int count;

// 콜벡 함수 
// 여기서 입력받은거 실행
// WndProc 어떤 입력이든 햇을때 나오는 녀석이라고 봐라
// 비동기함수
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
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
	// 초기화할 녀석들 한번실행되고 말 녀석들 여기다 넣어주면됨
	case WM_CREATE:
		count = 0;
		break;
    case WM_PAINT:		// 여기서 그리는거 한다고 보면됨
        {
			// gdiplus rect와 비슷 좌표값이 left top right bottom으로 들어가는 차이가있음
			RECT rect = { 100,100,200,200 };
			RECT rect2 = { 300,300,400,400 };
			// gdiplus랑 다른점 left, top 바꾸면 
			// gdiplus는 이동
			// gdiplus에선 x,y찍고 거기서 사각형 만드는거
			// 여기선 크기가 달라짐
			/*
				여기선 left top right bottom 점을 찍고 사각형을 지르는거
				-> 따라서 크기가 달라짐
			*/
            PAINTSTRUCT ps;
			// hdc 그림을 그리는데 필요한 모든 데이터가 들어가있는거
			// 그림 그릴때 graphics와 같다고 보면됨
			
			// 실제 출력은 beginpaint와 endpaint 사이에서 녀석만 실행됨

			// hdc 가 DC 출력에 관련된 모은것들이 들어있음
            HDC hdc = BeginPaint(hWnd, &ps);
			// beginPaint부터 hdc에 값들이 들어가는거
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다.
			TextOut(hdc, 300, 200, "요녀석이 이제 cout 대신 사용할 녀석",
				strlen("요녀석이 이제 cout 대신 사용할 녀석"));
			Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
			// 선의 색상, 두께, 안에 색도 바꿀 수 있음
			// 알파값은 변경안됨
			Rectangle(hdc, rect2.left, rect2.top, rect2.right, rect2.bottom);
			Ellipse(hdc, rect2.left, rect2.top, rect2.right, rect2.bottom);
			// api에서의 원은 rect로 사각형 만들고 그 안에 원을 그리는거

			// 선그리기 점 2개 필요 
			// 시작점 MoveToEx 끝점 LineTo
			// NULL 아무것도 없다 == 0
			MoveToEx(hdc, 100, 100, NULL);
			LineTo(hdc, 300, 150);
			// 계속 그리고 싶으면 LineTo만 작성해도됨
			LineTo(hdc, 200, 250);
			// 위에서 그리는 라인도 1 pixel

			// 정점 하나 그려주는 녀석
			// 컬러값 넣을때 COLLRREF 구조체 RGB(r,g,b)로 사용하면됨
			// 0 ~ 255 값 넣으면 됨
			for (int i = 0; i < 100; i++)
				SetPixel(hdc, 200, 400 + i, RGB(2 * i, 0, 2 * i));

			SetTextColor(hdc, RGB(0, 255, 0));
			// 이후부터는 계속 그 색상 그대로 유지됨
			TextOut(hdc, 500, 200, "글자 색상 변경",
				strlen("글자 색상 변경"));

			// 텍스트는 그라데이션 힘듬
			// 텍스트 한글자마다 색깔 설정 가능
			char str[128];
			// c++ 콘솔 화면 출력 cout << 10 << " 출력" << endl;
			// c printf("%d 출력\n", 10);
			sprintf_s(str, "%d 첫번째 숫자 %d 두번째 숫자 etc...",
				10, 20);
			// 콘솔에 출력하는게 아니라 sprintf_s는 str에 저장하는 역할
			SetTextColor(hdc, RGB(0, 0, 0));
			// 색깔 정보도 hdc에 들어가고 출력할때도 hdc에서 읽어옴
			TextOut(hdc, 200, 230, str, strlen(str));

			// 이때부터 출력하는거
			EndPaint(hWnd, &ps);
        }
        break;
	// api에서는 case로 입력 받거나
	// getKeyState 이와 같은 외부 함수로 받을 수도 있음 (그때 한별씨가 했던거)
	case WM_LBUTTONDOWN: // 마우스 왼쪽 버튼을 눌렀을 때
	{
		/*
			GetDC ReleaseDC 는 이미지 들어가면 한두번 하고 말꺼
			지금은 익숙해지기 위해 자주 사용하는거
		*/

		// 중괄호 별 의미없으나 가끔 이거 안하면 동작 안하기도 한다고함
		// GetDC는 데이터에 저장하기만 하는거
		// BeginPaint랑 EndPaint 모두 만나야만 출력됨
		HDC hdc = GetDC(hWnd);
		
		count++;

		TextOut(hdc, 100, 100 + 30 * count, "오늘 숙제는 구구단 띄어오기",
			strlen("오늘 숙제는 구구단 띄어오기"));

		ReleaseDC(hWnd, hdc);
	}
		break;
	case WM_RBUTTONDOWN:
	{
		HDC hdc = GetDC(hWnd);

		count--;

		TextOut(hdc, 100, 100 - 30 * count, "왼쪽 클릭시 1단 증가 오른쪽 클릭시 1단 감소",
			strlen("왼쪽 클릭시 1단 증가 오른쪽 클릭시 1단 감소"));

		ReleaseDC(hWnd, hdc);
	}
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
	과제
	한줄 조사
	콜백 함수
	DC
	PAINTSTRUCT
	GetDc/ReleaseDc
	BeginPaint() / EndPaint()
	WM_CREATE	// 창이 생성될때 딱 한번만 사용
	WM_PAINT

	조사해서 왜쓰는지 까지 알아보자

	오늘 배운게 window api라고 하면됨
*/

// 오늘(18.02.08)이 1달 수업 끝남 내일부터 신규 수업
// 내일부터 3층 c강의실 수업

/*
	gdiplus 
	매 그림마다 깜박꺼리던 문제
	더블 버퍼링 사용해서 해결
	그림하나에 그리고 다음 그림 보여주는 식 화면 전환해서

	-> 화면용 hdc 클리어 사용x
	-> backBuffer -> hdc 여기서 클리어 렌더 같이 사용

	-> 따라서 깜박거리지 않게됨
*/

/*
	18.02.08 
	과제

	1. 구구단 만들기
	구구단 출력
	왼쪽 키 누르면 1단 증가 
	오른 키 누르면 1단 감소 출력

	왼쪽 클릭시 1단 출력 
	한번더 2단
	오른쪽 클릭시 1단 감소

	2. InvalidateRect 한줄 조사해오기
	-> 이녀석 사용하면 지울 수 있음

	3. MoveToEx와 LineTo 이용해서 자기이름 써오기
	곡선은 (원)은 그리는걸로
	삼각함수 sin, cos 으로 그리면 LineTo 그릴 수 있음
	c++ 삼각함수로 원 그리기
	참고 아크코사인 사인의 역 알아야함 물체를 쏘아올릴 각도를 알아야할 때

	// setPixel 이용해서 하는 노가다 과제도 있음
	구글 애플로고 색깔입힌거 로그 찍기도 했었음
*/

/*
	넥슨 면접 문제 한번 공부해볼꺼
*/