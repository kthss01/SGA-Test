#pragma once

#include "SIngletonBase.h"

class TextData : public SingletonBase<TextData>
{
private:

public:
	TextData();
	~TextData();

	HRESULT Init();

	// Save
	void TextSave(char* saveFileName, vector<string> vStr);
	char* VectorArrayCombine(vector<string> vArray);

	// Load
	// �� �ٿ� ���� ������
	vector<string> TextLoad(char* loadFileName);
	// �����͵��� ����Ʈ
	vector<string> CharArraySeparation(char charArray[]);
};

#define TEXTDATA TextData::GetSingleton()

