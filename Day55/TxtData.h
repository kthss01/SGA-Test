#pragma once

#include "SIngletonBase.h"

// Ini 보다 Text가 Binary라 조금더 빠르긴 한데 알아보기 쉬운게 좋음

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
	// 한 줄에 넣을 데이터
	vector<string> TxTLoad(char* loadFileName);
	// 데이터들의 리스트
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

