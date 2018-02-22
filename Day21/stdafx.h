// 미리 컴파일된 파일

// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.

// 클래스 같은거 만들시 
// cpp에 같이 include 해서 들어감
// 변경 잘안되는 것들은 여기다 넣어두면 좋음

// 비주얼 스튜디오에서 
// 이미 빌드 할 때 코드가 수정되지 않는 파일은 넘어감 
// 따라서 stdafx.h에 수정하면 다시 검사하게 되니 수정되지 않는걸 넣어야함

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
////////////////////////////////////////////////////
// 내가 만든 헤더 파일 이곳에 추가
////////////////////////////////////////////////////
#include "CommonMacroFunction.h"

