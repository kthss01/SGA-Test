#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
//#include <  > // ��ġ �� �� ������� �ִ� ������ �ҷ��ͼ� ����ϰڴ�.
using namespace std;

void main()
{
	// ���� ����
	// �ڷ��� ������ + ������

	// ���� : �� ó�� ������� ��
	// ���� : �ȿ� ���� ä��ų� �ٲ� ��

	// �ڷ��� ������
	// int (������) -> -100, 0, 128

	// ����� ���ÿ� �ʱ�ȭ�ߴ�.
	// �������� ���� �� �� ������ �ڼ��ϰ�
	int maxHp = 100;
	int damage = -20;

	cout << maxHp << endl;
	cout << damage << endl;

	maxHp = 200;
	cout << maxHp << endl;
	maxHp = maxHp + damage;
	cout << maxHp + damage << endl;
	cout << maxHp << endl;

	damage = 10.99230f; // �������� �Ҽ� �Է½� �Ҽ��� ����
	cout << damage << endl;

	// �ڷ��� float(�Ǽ�) -> �Ҽ����� �ִ� ����
	//float maxHp = 135.2135f; // ���� �̸� ��� �� �� ����
	float fNumber = 135.2135f;

	cout << fNumber - damage << endl;

	// �ڷ��� bool(��, ����) -> true(1) false(0)
	bool isDamage = false;
	bool isAttack = true;

	// �ڷ��� char(����) 1�� 'a', '@', ' '
	char str = '5';
	char str2 = '6';
	cout << str << ',' << str2 << endl;
	cout << str + str2 << endl;

	// �ڷ��� string(���ڿ�) "�츮�� ����ϴ� �⺻ �����???"

	string name = "ĳ���� �̸� : ";

	cout << name << endl;

	cout << "�ڽ��� �����ϴ� ���ڸ� �ϳ� �Է� �ϼ��� : ";
	int number;
	string itemInfo;
	// cin ���� �Է��� �� ���� �༮
	//cin >> number;
	//cout << "�Է��Ͻ� ���ڴ� " << number << "�Դϴ�." << endl;
	//cin >> itemInfo;
	//cout << itemInfo << endl;

	// cin
	// �����̽��ٷ� ����

	// �ָ� ���� -> ����(�ݺ���, ���ǹ�) ���ͳݿ��� ã�Ƽ� 
	// ���� ��� (c++ �ݺ���, ���ǹ� ����) �ؿ��� : �޸����̳� ��å�� �����

	// rand() -> �������� ������ �༮ ���� ���� ����
	// ���� �߻��� ���� �����ϰ� ����� �ִ� �༮
	srand(time(NULL));
	cout << rand() % 10 << endl; // 0 ~ 9
	cout << rand() % 10 + 1 << endl; // 0+1 ~ 9+1 -> 1 ~ 10

	int random = rand() % 100;
	
	// �ָ� ���� ���ǹ�, �ݺ��� ���� ���� ��� 
	
}