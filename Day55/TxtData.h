#pragma once

#include "SIngletonBase.h"

// Ini 보다 Text가 Binary라 조금더 빠르긴 한데 알아보기 쉬운게 좋음

class TxtData : public SingletonBase<TxtData>
{
private:

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
};

#define TXTDATA TxtData::GetSingleton()

