#include <cstdio>

// char�� ���� 5������
// short ������ ���� ����
// short �������� ������ ©�� 7byte�� ��
// ū �༮�� �������� ©�� 

struct tagSize{
	char str;
	char str1;
	char str2;
	char str3;
	char str4;

	short sNum;	// 2
};

int main() {

	printf("char size : %d\n", sizeof(char));
	printf("struct size : %d\n", sizeof(tagSize));

	return 0;
}