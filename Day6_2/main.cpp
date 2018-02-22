#include <iostream>
#include <string>

using namespace std;

// 문자열 함수
void main()
{
	// strlen : 문자열의 길이
	// NULL문자 제외 한글 2byte, 나머지 1byte

	char str1[20] = "문자열의 길이";
	int len = strlen(str1);
	cout << "결과값은?? : " << len << endl;

	// strcmp : 문자열 비교
	// 아스키 코드로 크고 작음 비교
	// 1. 양수	반환시 1번째 인자가 2번째 인자보다	크면 
	// 2. 음수	반환시 1번째 인자가 2번째 인자보다	작으면
	// 3. 0		반환시 1번째 인자가 2번째 인자와	같으면
	char str2[20] = "abc";
	char str3[20] = "abc";
	char str4[20] = "abd";

	int result = strcmp(str2, str3);
	cout << "문자열이 같을 때 : " << result << endl;
	int result2 = strcmp(str2, str4);
	cout << "1번째 인자가 작을 때 : " << result2 << endl;
	int result3 = strcmp(str4, str2);
	cout << "1번째 인자가 클 때 : " << result3 << endl;
	
	// strcpy : 문자열 복사
	char str5[20] = "hello....";
	char str6[20];

	strcpy(str6, str5);
	cout << "문자열 복사 : " << str6 << endl;

	// strtok : 문자열 자를 때 (자르는 조건 /, , _, [, ])
	char str7[20] = "abcd/efg";
	strtok(str7, "/");
	cout << str7 << endl;

	strtok(NULL, "/");
	cout << str7 << endl;

	// strstr : 특정 문자의 위치
	char str9[20] = "abcd/efg";
	char* str10 = strstr(str9, "/");

	cout << str10 << endl;

	// strcat : 문자열을 합칠 때
	char str11[20] = "abcd";
	char str12[20] = "efgh";

	strcat(str11, str12);
	cout << str11 << endl;
	cout << str12 << endl;

	string str13 = "문자열을 ";
	string str14 = "합치는 방법??";
	string str15 = str13 + str14;

	cout << str15 << endl;

	// 과제
	/*
		1번 열거형 (enum)에 대한 한 줄 조사
		2번 문자열 뒤집기 -> 예전 면접 문제 중 하나 // 구두로 설명하는 문제
		*요즘 특정 문자를 제외하고 문자열 뒤집기
	*/

	char str16[20] = "abcdefgh";

	cout << str16 << endl;

	// 출력 될 때 hgfdecba 
	/// 해결되면 "abs/sae&stge[" 이것도 풀어보기
}