// 메모리 해제 되었는지 확인하는 체크
// 디버깅(F5)으로 확인해야함
// delete delete[] 실수는 확인할 수 없음
// CrtSetBreakAlloc() 이거 

#include <crtdbg.h>

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF |
		_CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(72);

	int* pNum = new int[10];

	// 그냥 돌리면 출력창에 뜸

	//delete[] pNum;


	return 0;
}