#include <iostream>
#include <time.h>
#include <Windows.h>
#include <string>

using namespace std;

// ����ü struct

struct Image
{
	string image;
	int imageWidth;
	int imageHeight;
};

struct Character
{
	string id;
	int level;
	float maxExp;
	float currentExp;
	float maxHp;
	float currentHp;
	int damage;
	bool isDie;
	float positionX;
	float positionY;
	Image image;
};

void main() {
	srand(time(NULL));

	Character unit[10];

	Character knight;

	knight.id = "���";
	knight.level = 0;
	knight.isDie = false;
	knight.currentExp = 0;
	knight.damage = 10;
	knight.maxHp = knight.currentHp = 100;

	//cout << knight.id << endl;
	//cout << knight.level << endl;
	//cout << knight.damage << endl;
	//cout << knight.maxHp << endl;
	//cout << knight.currentHp << endl;

	Character wizard;

	wizard.id = "������";
	wizard.maxHp = wizard.currentHp = 80;
	wizard.damage = 5;
	wizard.level = 1;
	wizard.isDie = false;
	

	Character monster;

	monster.id = "����";
	monster.level = 10;
	monster.maxHp = monster.currentHp = 200;
	monster.damage = 20;
	monster.isDie = false;

	while (true) {
		cout << "����� ü�� : " << knight.currentHp << endl;
		cout << "�������� ü�� : " << wizard.currentHp << endl;
		cout << "������ ü�� : " << monster.currentHp << endl;
		int selectNumber;

		if (knight.isDie == false) {
			cout << "����� ��" << endl;
			cout << "0�� ����, 1�� ȸ��" << endl;
			selectNumber = rand() % 2;
			//cin >> selectNumber;
			switch (selectNumber)
			{
			case 0:
				cout << "����� ���� " << endl;
				monster.currentHp -= knight.damage;
				cout << "������ ü�� -> " <<
					monster.currentHp << endl;
				break;
			case 1:
				cout << "����� ȸ��" << endl;
				if (knight.currentHp <= knight.maxHp) {
					knight.currentHp += 10;
				}
				if (knight.currentHp > knight.maxHp) {
					knight.currentHp = knight.maxHp;
				}
				break;
			default:
				cout << "�� �� �Է�" << endl;
				break;
			}
		}

		if (wizard.isDie == false) {
			cout << "�������� ��" << endl;
			cout << "0�� ����, 1�� ȸ��" << endl;
			selectNumber = rand() % 2;
			//cin >> selectNumber;
			switch (selectNumber)
			{
			case 0:
				cout << "�������� ���� " << endl;
				monster.currentHp -= wizard.damage;
				cout << "������ ü�� -> " <<
					monster.currentHp << endl;
				break;
			case 1:
				cout << "�������� ȸ��" << endl;
				if (wizard.currentHp <= wizard.maxHp) {
					wizard.currentHp += 10;
				}
				if(wizard.currentHp > wizard.maxHp) {
					wizard.currentHp = wizard.maxHp;
				}
				break;
			default:
				cout << "�� �� �Է�" << endl;
				break;
			}
		}
		
		if (monster.isDie == false) {
			cout << "������ ����" << endl;
			// 30% Ȯ���� ���� ����
			int random = rand() % 3;
			if (random == 0) {
				cout << "������ ����" << endl;
				Sleep(1000);
				// ��� ���� (��糪 ������)
				int random2 = rand() % 2;
				switch (random2)
				{
				case 0:
					cout << "���Ͱ� ��縦 ����" << endl;
					knight.currentHp -= monster.damage;
					break;
				case 1:
					cout << "���Ͱ� �����縦 ����" << endl;
					wizard.currentHp -= monster.damage;
					break;
				default:
					break;
				}
			}
			else {
				cout << "��������" << endl;
			}
		}

		if (monster.currentHp <= 0) {
			monster.isDie = true;
		}
		if (knight.currentHp <= 0) {
			knight.isDie = true;
		}
		if (wizard.currentHp <= 0) {
			wizard.isDie = true;
		}

		if (monster.isDie == true ||
			(knight.isDie == true && wizard.isDie == true)) {
			break;
		}
		Sleep(2000);
		system("cls");
	}

	/// �ܼ� Ŀ�� ��ǥ �̵��ϱ� 
	/// �̰͵� Ȱ���غ��� ���ٰ� �Ͻ� ���� �ַܼ� ���� ����� �� ��
}