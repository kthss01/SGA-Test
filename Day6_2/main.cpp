#include <iostream>
#include <string>

using namespace std;

// ���ڿ� �Լ�
void main()
{
	// strlen : ���ڿ��� ����
	// NULL���� ���� �ѱ� 2byte, ������ 1byte

	char str1[20] = "���ڿ��� ����";
	int len = strlen(str1);
	cout << "�������?? : " << len << endl;

	// strcmp : ���ڿ� ��
	// �ƽ�Ű �ڵ�� ũ�� ���� ��
	// 1. ���	��ȯ�� 1��° ���ڰ� 2��° ���ں���	ũ�� 
	// 2. ����	��ȯ�� 1��° ���ڰ� 2��° ���ں���	������
	// 3. 0		��ȯ�� 1��° ���ڰ� 2��° ���ڿ�	������
	char str2[20] = "abc";
	char str3[20] = "abc";
	char str4[20] = "abd";

	int result = strcmp(str2, str3);
	cout << "���ڿ��� ���� �� : " << result << endl;
	int result2 = strcmp(str2, str4);
	cout << "1��° ���ڰ� ���� �� : " << result2 << endl;
	int result3 = strcmp(str4, str2);
	cout << "1��° ���ڰ� Ŭ �� : " << result3 << endl;
	
	// strcpy : ���ڿ� ����
	char str5[20] = "hello....";
	char str6[20];

	strcpy(str6, str5);
	cout << "���ڿ� ���� : " << str6 << endl;

	// strtok : ���ڿ� �ڸ� �� (�ڸ��� ���� /, , _, [, ])
	char str7[20] = "abcd/efg";
	strtok(str7, "/");
	cout << str7 << endl;

	strtok(NULL, "/");
	cout << str7 << endl;

	// strstr : Ư�� ������ ��ġ
	char str9[20] = "abcd/efg";
	char* str10 = strstr(str9, "/");

	cout << str10 << endl;

	// strcat : ���ڿ��� ��ĥ ��
	char str11[20] = "abcd";
	char str12[20] = "efgh";

	strcat(str11, str12);
	cout << str11 << endl;
	cout << str12 << endl;

	string str13 = "���ڿ��� ";
	string str14 = "��ġ�� ���??";
	string str15 = str13 + str14;

	cout << str15 << endl;

	// ����
	/*
		1�� ������ (enum)�� ���� �� �� ����
		2�� ���ڿ� ������ -> ���� ���� ���� �� �ϳ� // ���η� �����ϴ� ����
		*���� Ư�� ���ڸ� �����ϰ� ���ڿ� ������
	*/

	char str16[20] = "abcdefgh";

	cout << str16 << endl;

	// ��� �� �� hgfdecba 
	/// �ذ�Ǹ� "abs/sae&stge[" �̰͵� Ǯ���
}