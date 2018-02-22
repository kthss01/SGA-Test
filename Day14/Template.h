#pragma once
#include "MainGame3.h"

// ���ø� : �������� �Լ� �� Ŭ������ ���� Ʋ�̶�� ����

// Ŭ�������� ���ø��ϸ� Ŭ���� �����Ѱ� �� ���ø�
class Template
{
public:
	Template();
	~Template();

	// �̷��Ե� ���������� ���ø����� ����
	//void Output(int data);
	//void Output(float data);
	//void Output(char* data);

	template<typename T>	// �ٷ� �Ʒ��� ����
	void Output(T data);
};

// ����� �����ϸ� cpp�� �۾��� �� ����
// �Լ� ȣ���ϴµ��� ���� ����
// inline ���̸� ������ ���� ����ٰ� ���� ��
template<typename T>
inline void Template::Output(T data)
{
	cout << "������ : " << data << endl;
}
