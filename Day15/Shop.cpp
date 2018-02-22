#include "Shop.h"



Shop::Shop()
{
}


Shop::~Shop()
{
	
}

/*
	strcat
	strcat_s	// 새로 만들어진 녀석
	strcpy
	strcpy_s	// 새로 만들어진 녀석

	C언어 예전부터 문제점있어서 함수 추가

	비슷한거
	int;
	INT;		// 새로 만들어진 거
	float;
	FLOAT;		// 새로 만들어진 거
	bool;
	BOOL;		// 새로 만들어진 거
	만든 이유는 동일 : 문제가 있어서 추가로 만든거

	2017 부터 오류가 생기니까 _s 이거 쓰라고 제안하는거 
	가능하면 이거 쓰자
*/

void Shop::ItemSetup()
{
	//// 방어구
	//tagItemInfo item;
	//item.itemKind = ITEM_ARMOR;
	//item.name = "가죽 바지";
	//item.price = 50;
	//item.attribute = 1;
	//item.description = "가죽으로 만든 바지";
	//item.count = 1;
	//m_vItem.push_back(item);

	//item.itemKind = ITEM_ARMOR;
	//item.name = "쇠 바지";
	//item.price = 150;
	//item.attribute = 5;
	//item.description = "쇠로 만든 바지";
	//item.count = 1;
	//m_vItem.push_back(item);

	//// 무기
	//item.itemKind = ITEM_WEAPON;
	//item.name = "한손검";
	//item.price = 100;
	//item.attribute = 5;
	//item.description = "한손으로 들 수 있는 검";
	//item.count = 1;
	//m_vItem.push_back(item);

	//item.itemKind = ITEM_WEAPON;
	//item.name = "광선검";
	//item.price = 250;
	//item.attribute = 15;
	//item.description = "영화 스타워즈 오마주";
	//item.count = 1;
	//m_vItem.push_back(item);

	tagItemInfo item;

	FILE* fp;
	fopen_s(&fp, "Text/Item.txt", "r");	// 파일경로 프로젝트 기준 상대경로
	// s가 safe 의미
	// 절대경로로 적어도 됨
	//fopen_s(&fp, "C:/Users/kthss/source/repos/게임 아카데미/Day15/Text/Item.txt", "r");

	char* str = new char[1024]; // 자른 내용을 저장할 녀석
	memset(str, 0, 1024); // memset 초기화 해주는 함수, 0으로 1024만큼 초기화
	// 파일의 마지막 중이 아닐 때까지 읽겠다
	// feof(fp) 마지막이면 true 아니면 false 반환
	while (!feof(fp)) {
		// 한줄씩 끊어 읽을 데이터 변수 선언 및 초기화
		char* szBuff = new char[1024];
		memset(szBuff, 0, 1024);
		fgets(szBuff, 1024, fp);

		// 예외 처리 문자열의 길이가 0이면 계속 진행
		// 파일 안에 엔터로 구분지은거 (예외 처리)
		if (strlen(szBuff) == 0)
			continue;

		// szBuff = [1][초보자 의상][50][2][시작 아이템][2]
		// str = "1"(문자열)
		//str = strtok(szBuff, "[]");
		str = strtok_s(szBuff, "[]", &szBuff);	// 자를 문자열, 자를 기준, 자르고 난 녀석을 저장할지

		item.itemKind = (ITEM)atoi(str);	// atoi 문자열 -> 정수로 바꿔줌
		// 반대방법 정수 -> 문자열 : itoa

		// 한번 자른 녀석들 계속 자르려면 NULL 넣어주어야함
		// strtok에 str 넣으면 계속 1만 나옴

		// szbuff = 초보자 의상][50][2][시작 아이템][2]
		// str = "초보자 의상"
		//str = strtok(NULL, "[]");
		str = strtok_s(szBuff, "[]", &szBuff);
		item.name = str;

		// szbuff = 50][2][시작 아이템][2]
		// str = "50"
		//str = strtok(NULL, "[]");
		str = strtok_s(szBuff, "[]", &szBuff);
		item.price = atoi(str);

		// szbuff = 2][시작 아이템][2]
		// str = "2"
		//str = strtok(NULL, "[]");
		str = strtok_s(szBuff, "[]", &szBuff);
		item.attribute = atoi(str);

		// szbuff = 시작 아이템][2]
		// str = "시작 아이템"
		//str = strtok(NULL, "[]");
		str = strtok_s(szBuff, "[]", &szBuff);
		item.description = str;

		// szbuff = 2]
		// str = "2"
		//str = strtok(NULL, "[]");
		str = strtok_s(szBuff, "[]", &szBuff);
		item.count = atoi(str);

		m_vItem.push_back(item);
	}
	fclose(fp);
}

int Shop::ItemOutput(int num)	// Inventory.cpp ShowInventory() 에 복사
{
	int itemCount = 0;
	m_viItem = m_vItem.begin();
	for (m_viItem; m_viItem != m_vItem.end(); ++m_viItem) {
		// 내가 선택한 아이템 종류만 출력
		if (m_viItem->itemKind != num) continue;
		// i++ (사용하고 증가), ++i(증가되고 사용) 차이점
		// 언제 증가하냐 차이
		cout << "==================================" << endl;
		cout << "아이템 번호 : " << ++itemCount << endl;
		cout << "이름 : " << m_viItem->name << endl;
		cout << "가격 : " << m_viItem->price << endl;
		cout << "능력치 : " << m_viItem->attribute << endl;
		cout << "설명 : " << m_viItem->description << endl;
		cout << "갯수 : ";
		// 삼항 연산자 (조건) ? 참 : 거짓
		(m_viItem->count > 0) 
			? cout << m_viItem->count << endl
			: cout << "매진" << endl;
		cout << "==================================" << endl;
	}
	return itemCount;
}

tagItemInfo Shop::BuyItem(int itemKind, int num, int & gold)
{
	tagItemInfo buyItem;
	buyItem.itemKind = ITEM_EMPTY;
	int itemCount = 0;	// 화면에 출력되었을 때 아이템 번호 의미
	m_viItem = m_vItem.begin();
	for (m_viItem; m_viItem != m_vItem.end(); ++m_viItem) {
		// 내가 선택한 아이템만 출력
		if (m_viItem->itemKind != itemKind) continue;

		// 내가 선택한 번호가 있을 때
		if (++itemCount == num) {
			// 구매할 돈이 있을 때
			if (gold >= m_viItem->price) {
				// 구매할 아이템 갯수가 남아있을 때
				if (m_viItem->count > 0) {
					cout << m_viItem->name << "을 "
						<< m_viItem->price << "gold에 구매" << endl;
					gold -= m_viItem->price;
					m_viItem->count--;
					buyItem = *m_viItem;	// 아이템의 정보 넣어줌
				}
				else {
					cout << "재고가 없다" << endl;
				}
			}
			else {
				cout << "돈이 없다" << endl;
			}
			// 아이템 찾았으므로 끝
			break;
		}
	}
	return buyItem;
}

void Shop::AddItem(tagItemInfo item) // Inventory.cpp AddItem() 복사
{
	bool isNewItem = true;

	m_viItem = m_vItem.begin();
	for (m_viItem; m_viItem != m_vItem.end(); ++m_viItem) {
		// 아이템 같은 종류인지 확인
		if (m_viItem->itemKind != item.itemKind) continue;

		// strcmp 같음 string 안에 compare 함수 있음
		// 아이템 이름 같으면 갯수만 증가
		if (m_viItem->name.compare(item.name) == 0) {
			m_viItem->count++;
			isNewItem = false;
			break;
		}
	}

	if (isNewItem == true) {
		m_vItem.push_back(item);
	}
}


