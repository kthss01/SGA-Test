#include <iostream>

using namespace std;

void main()
{
	// ���ǹ�
	/*
		1. 
		if (����)
		{
			��
		}
		else
		{
			����
		}
		switch
	*/

	/*
	bool isAttack = false;
	if (isAttack) 
	{
		cout << "�����ߴ�" << endl;
	}
	else 
	{
		cout << "�������� �ʾҴ�" << endl;
	}
	*/

	// ���ǹ� ���� ����ϴ� ���� : ���� �ùķ��̼� ����

	// ������ 
	// ���� ������ int num = 10; a = b -> a�� b�� �ִ´�.
	// ��Ģ ������ '+'. '-', '*', '/', '%'
	// �� ������ '>', '<', '>=', '<=', '==', '!='
	// ��� ������ (and, or) '&&' (and) '||' (or)
	// (and)	a(��)	&& b(��)	-> ��		
	//			a(����) && b(��)	-> ����
	//			a(����) && b(����)	-> ����
	/*
			ex) 
				a(��) Ű�� ���ȴ���?
			&&	b(��) ���Ͱ� �����Ÿ� �ȿ� �ִ���?
			-> �� -> ���) ���� ü�� ���� 
	*/
	//***** back space ���� \ �̰� ����Ʈ �����ָ� | ����

	// (or)		a(��)	|| b(��)	-> ��
	//			a(��)	|| b(����)	-> ��
	//			a(����)	|| b(����)	-> ����	
	/*
			ex)
				a	����Ű�� ��������
			||	b	ü���� ������ �ִ���?
			-> ���) ������ �Դ´�.
	*/
	//***** &(reference)

	bool isAttack = false;
	int attackRange = 0;

	if (isAttack == true && attackRange < 1) 
	{
		cout << "���� �ߴ�" << endl;
	}
	else if(isAttack == true && attackRange > 1)
	{
		cout << "������ ������ ��Ÿ��� �����ߴ�" << endl;
	}
	else
	{
		cout << "���� ��ư�� ������ �ʾҴ�" << endl;
	}

	// switch(����)
	int random = 20;
	char str = '!';
	/*
	switch (random) 
	{
	case 0:
		cout << "random �� 0�� ����" << endl;
		break;
	case -1:
		cout << "random �� -1�� ����" << endl;
		break;
	case 100:
		cout << "random �� 100�� ����" << endl;
		break;
	default:
		cout << "�� ���� ���� �־���" << endl;
		break;
	}
	*/
	switch (str) 
	{
	case '!':
		cout << "!" << endl;
	case 'a':
		cout << "a" << endl;
		break;
	case 'b':
		cout << "b" << endl;
		break;
	case 'c':
		cout << "c" << endl;
		break;
	default:
		cout << "�� ���� ���� �־���" << endl;
		break;
	}

	cout << "switch ���� " << endl;
	// break; ���ǹ��̳� �ݺ��������� ���Ǹ�
	// ���ǹ��̳� �ݺ����� ���� �� �� ���ȴ�

	/* 
	���� �غ� �κ�
	namespace, using
	-> using namespace std; �� ���� ����
	ǥ�� ���̺귯���� ��û���� ���Ƽ� Ŭ������ �Լ� �̸� ���� ��
	�浹�� �� �� ���� �浹 ������ ���� std��� �̸��� ���ӽ����̽��� 
	ǥ�� ���̺귯���� ���� ��Ų��
	�̿� ���� ���ο� ��� �̸��� ������ �Ǵµ� .h�� �����ϴ� ��� ����
	<iostream> <string>
	using 
		���ӽ����̽�::~ ���°� ���ŷο�Ƿ� �װ� ���� ���� using ���°�
	enum 
	*/

}