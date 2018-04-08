#include "stdafx.h"
#include "TxtData.h"


TxtData::TxtData()
{
}


TxtData::~TxtData()
{
}

HRESULT TxtData::Init()
{
	return S_OK;
}

void TxtData::TxTSave(char * saveFileName, vector<string> vStr)
{
	// api�� �������ִ� save �Լ� ���
	HANDLE file;
	char str[256];
	DWORD write;

	// �������ִµ� ũ����� ���������� ��
	strncpy_s(str, 256, VectorArrayCombine(vStr), 256);

	// CreateFile Binary �������� ��
	// Binary 16���� ������ �������� ��
	// Binary �ѱ� �������� ������ �־���
	file = CreateFile(
		saveFileName,	// ������ ���� �Ǵ� �ε��� ������ �̸�
		GENERIC_WRITE,	// �����̳� ��ġ�� ����ų� ������ ����
		0,				// ���� ���� ��� �Է�
		NULL,			// ���� �Ǵ� ��ġ�� �� �� ���� �� Ư��
		// �׻� ó������ �ۼ��ϰڴٴ°� �� �����
		// ���� �ٲ��ָ� ���κ��� ���� �� ����
		CREATE_ALWAYS,	// �����̳� ��ġ�� �� �� ���� �ൿ
		FILE_ATTRIBUTE_NORMAL,	// ����, ��ġ�� �� ��, ���� �� ���� Ư��
		NULL			// ������� ������ ���� �� Ư�� etc ����Ǵ� �ڵ�
	);

	WriteFile(file, str, 256, &write, NULL);
	CloseHandle(file);
}

char * TxtData::VectorArrayCombine(vector<string> vArray)
{
	char str[256];
	ZeroMemory(str, sizeof(str));

	for (int i = 0; i < vArray.size(); i++) {
		strncat_s(str, 256, vArray[i].c_str(), 256);

		// ������ ���ڴ� �����Ϸ��� �ؼ�
		if ((i + 1) < vArray.size()) {
			strcat_s(str, ",");
		}
		
		//// �̰� �߰��ϸ� ���� -> �̷��� �ϸ� �ȵɵ�
		//// �о�� �� ���� ����
		//if (i == vArray.size() - 1)
		//	strcat_s(str, "\r\n\0");
	}

	return str;
}

vector<string> TxtData::TxTLoad(char * loadFileName)
{
	HANDLE file;
	char str[256];
	DWORD read;

	ZeroMemory(str, sizeof(str));

	file = CreateFile(
		loadFileName,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	ReadFile(file, str, 256, &read, NULL);
	CloseHandle(file);

	return CharArraySeparation(str);
}

vector<string> TxtData::CharArraySeparation(char charArray[])
{
	vector<string> vArray;
	char* separator = (char*)",";

	char* context = NULL;

	char* token = strtok_s(charArray, separator, &context);
	vArray.push_back(token);
	while (token) {
		token = strtok_s(NULL, separator, &context);
		if(token != NULL)
			vArray.push_back(token);
	}

	return vArray;
}

void TxtData::TextWrite(vector<string> vStr)
{
	char str[256];
	DWORD write;

	strncpy_s(str, 256, VectorArrayCombine(vStr), 256);
	WriteFile(file, str, 256, &write, NULL);
}

vector<vector<string>> TxtData::TextRead()
{
	vector< vector<string> > vvStr;

	char str[256];
	DWORD read = 0;

	int cnt = 0;
	while(true) {
		ReadFile(file, str, 256, &read, NULL);
		if (read <= 0) break;
		vvStr.push_back(CharArraySeparation(str));
	};


	return vvStr;
}
