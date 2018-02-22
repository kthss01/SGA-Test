#pragma once
#include <Windows.h>
#include "Shop.h"
#include "Player.h"
enum LOCATION {	// ��ġ
	LOCATION_SHOP = 1,
	LOCATION_SELL_INVENTORY,
	LOCATION_INVENTORY
};

// Ŭ������ ��üȭ�ϱ� ���ؼ� �����Ҵ� �ϴ°� ����

class MainGame4
{
private:
	Shop* m_shop;			// ���� Ŭ����
	Player* m_player;
	LOCATION m_location;	// ��ġ

	int m_gold;
	int m_selectNum;
public:
	MainGame4();
	~MainGame4();

	// ����, �κ��丮 �̵�
	void SetLocation(int number);
	// ���� ȭ��
	void SetMainPage();
	// ���� ȭ��
	void SetShopPage();
	// ������ �������� �����ִ� �Լ�
	void SetShopItemPage(int itemKind);
	// �κ��丮 ���� �ǸŸ� �����ִ� �Լ�
	void SetSellInventoryPage();
	// �κ��丮 �����ִ� �Լ�(������)
	void SetInventoryPage();
};

