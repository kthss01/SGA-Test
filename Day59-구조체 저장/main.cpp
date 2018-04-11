#include <cstdio>

// char만 들어가면 5이지만
// short 값까지 같이 들어가면
// short 기준으로 공간이 짤림 7byte가 됨
// 큰 녀석을 기점으로 짤림 

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