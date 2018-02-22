#include <iostream>
#include <time.h>
#include <Windows.h>
#include <string>

using namespace std;

// 구조체 struct

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

	knight.id = "기사";
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

	wizard.id = "마법사";
	wizard.maxHp = wizard.currentHp = 80;
	wizard.damage = 5;
	wizard.level = 1;
	wizard.isDie = false;
	

	Character monster;

	monster.id = "몬스터";
	monster.level = 10;
	monster.maxHp = monster.currentHp = 200;
	monster.damage = 20;
	monster.isDie = false;

	while (true) {
		cout << "기사의 체력 : " << knight.currentHp << endl;
		cout << "마법사의 체력 : " << wizard.currentHp << endl;
		cout << "몬스터의 체력 : " << monster.currentHp << endl;
		int selectNumber;

		if (knight.isDie == false) {
			cout << "기사의 턴" << endl;
			cout << "0번 공격, 1번 회복" << endl;
			selectNumber = rand() % 2;
			//cin >> selectNumber;
			switch (selectNumber)
			{
			case 0:
				cout << "기사의 공격 " << endl;
				monster.currentHp -= knight.damage;
				cout << "몬스터의 체력 -> " <<
					monster.currentHp << endl;
				break;
			case 1:
				cout << "기사의 회복" << endl;
				if (knight.currentHp <= knight.maxHp) {
					knight.currentHp += 10;
				}
				if (knight.currentHp > knight.maxHp) {
					knight.currentHp = knight.maxHp;
				}
				break;
			default:
				cout << "잘 못 입력" << endl;
				break;
			}
		}

		if (wizard.isDie == false) {
			cout << "마법사의 턴" << endl;
			cout << "0번 공격, 1번 회복" << endl;
			selectNumber = rand() % 2;
			//cin >> selectNumber;
			switch (selectNumber)
			{
			case 0:
				cout << "마법사의 공격 " << endl;
				monster.currentHp -= wizard.damage;
				cout << "몬스터의 체력 -> " <<
					monster.currentHp << endl;
				break;
			case 1:
				cout << "마법사의 회복" << endl;
				if (wizard.currentHp <= wizard.maxHp) {
					wizard.currentHp += 10;
				}
				if(wizard.currentHp > wizard.maxHp) {
					wizard.currentHp = wizard.maxHp;
				}
				break;
			default:
				cout << "잘 못 입력" << endl;
				break;
			}
		}
		
		if (monster.isDie == false) {
			cout << "몬스터의 차례" << endl;
			// 30% 확률로 공격 시작
			int random = rand() % 3;
			if (random == 0) {
				cout << "몬스터의 공격" << endl;
				Sleep(1000);
				// 대상 선택 (기사나 마법사)
				int random2 = rand() % 2;
				switch (random2)
				{
				case 0:
					cout << "몬스터가 기사를 공격" << endl;
					knight.currentHp -= monster.damage;
					break;
				case 1:
					cout << "몬스터가 마법사를 공격" << endl;
					wizard.currentHp -= monster.damage;
					break;
				default:
					break;
				}
			}
			else {
				cout << "빗나갔다" << endl;
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

	/// 콘솔 커서 좌표 이동하기 
	/// 이것도 활용해보면 좋다고 하심 만약 콘솔로 게임 만들게 될 때
}