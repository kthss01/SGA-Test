// �޸� ���� �Ǿ����� Ȯ���ϴ� üũ
// �����(F5)���� Ȯ���ؾ���
// delete delete[] �Ǽ��� Ȯ���� �� ����
// CrtSetBreakAlloc() �̰� 

#include <crtdbg.h>

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF |
		_CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(72);

	int* pNum = new int[10];

	// �׳� ������ ���â�� ��

	//delete[] pNum;


	return 0;
}