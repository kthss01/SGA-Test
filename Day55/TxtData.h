#pragma once

#include "SIngletonBase.h"

// Ini ���� Text�� Binary�� ���ݴ� ������ �ѵ� �˾ƺ��� ����� ����

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
	// �� �ٿ� ���� ������
	vector<string> TxTLoad(char* loadFileName);
	// �����͵��� ����Ʈ
	vector<string> CharArraySeparation(char charArray[]);
};

#define TXTDATA TxtData::GetSingleton()

