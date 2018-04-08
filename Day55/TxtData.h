#pragma once

#include "SIngletonBase.h"

// Ini ���� Text�� Binary�� ���ݴ� ������ �ѵ� �˾ƺ��� ����� ����

class TxtData : public SingletonBase<TxtData>
{
private:
	HANDLE file;
public:
	TxtData();
	~TxtData();

	HRESULT Init();

	// Save
	void TxTSave(char* saveFileName, vector<string> vStr);
	char* VectorArrayCombine(vector<string> vArray);

	// Load
	// �� �ٿ� ���� ������
	vector<string> TxTLoad(char* loadFileName);
	// �����͵��� ����Ʈ
	vector<string> CharArraySeparation(char charArray[]);

	void CreateWriteTextDataHandle(char* fileName) {
		file = CreateFile(fileName, GENERIC_WRITE,
			0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	}
	void CreateReadTextDataHandle(char* fileName) {
		file = CreateFile(fileName, GENERIC_READ,
			0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	}
	void TextWrite(vector<string> vStr);
	vector< vector<string> > TextRead();
	void CloseTextDataHandle() { CloseHandle(file); }
};

#define TXTDATA TxtData::GetSingleton()

