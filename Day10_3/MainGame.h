#pragma once
/*
	��ü ���� �ڵ�	- ���������� �������� �ֵ� ����
	��ü -> ������, �ൿ, identity(Ư��) 
	.h(���), .cpp

	-> .h (����) int num; void Add();	// ���� ������ ����� ���� ���Ե�

*/
/*
	���� ������
	public, protected, private

	public -> ��� Ŭ�������� ����� �� �ִ�
	protected -> ��� (�θ� �ڽ� ����)�� ���� Ŭ���������� ��� ����
	private -> �ڱ� �ڽŸ� ����� �� �ִ�
*/

/*
	������ -> Ŭ������ ó�� �������� �� 1�� ����
	�Ҹ��� -> Ŭ������ ó�� �Ҹ���� ��	1�� ����
*/

class MainGame
{
private:
	int m_x, m_y;	// Ŭ���� �� �ɹ� ���� ����

public:
	MainGame();		// ������
	~MainGame();	// �Ҹ���

	// �巡�� �� ���� Ŭ���ϸ� �ڵ����� cpp���� ���� ����� ��
	void PublicFunction();

protected:
	void ProtectedFunction();

private:
	void PrivateFunction();
};

