#pragma once
#include <Windows.h>
#include "Shop.h"
#include "Player.h"
enum LOCATION {	// 위치
	LOCATION_SHOP = 1,
	LOCATION_SELL_INVENTORY,
	LOCATION_INVENTORY
};

// 클래스들 객체화하기 위해선 동적할당 하는게 좋다

class MainGame4
{
private:
	Shop* m_shop;			// 상점 클래스
	Player* m_player;
	LOCATION m_location;	// 위치

	int m_gold;
	int m_selectNum;
public:
	MainGame4();
	~MainGame4();

	// 상점, 인벤토리 이동
	void SetLocation(int number);
	// 메인 화면
	void SetMainPage();
	// 상점 화면
	void SetShopPage();
	// 상점의 아이템을 보여주는 함수
	void SetShopItemPage(int itemKind);
	// 인벤토리 상점 판매를 보여주는 함수
	void SetSellInventoryPage();
	// 인벤토리 보여주는 함수(장착용)
	void SetInventoryPage();
};

