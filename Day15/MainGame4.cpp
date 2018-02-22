#include "MainGame4.h"


// �ʱ�ȭ
MainGame4::MainGame4()
{
	// ���� Ŭ���� �����Ҵ� �� �ʱ�ȭ
	m_shop = new Shop;
	m_shop->ItemSetup();

	m_player = new Player;
	m_player->InputPlayer();

	m_gold = 10000;
	m_selectNum = 0;

	SetMainPage();
}

MainGame4::~MainGame4()
{
	delete m_shop;
	delete m_player;
}

void MainGame4::SetLocation(int number)
{
	switch (number)
	{
	case LOCATION_SHOP:
		SetShopPage();
		break;
	case LOCATION_SELL_INVENTORY:
		SetSellInventoryPage();
		break;
	case LOCATION_INVENTORY:
		SetInventoryPage();
		break;
	default:
		SetMainPage();
		break;
	}
}

void MainGame4::SetMainPage()
{
	system("cls");
	cout << "===============��ġ==============" << endl;
	cout << "1.���� 2. �κ��丮[�Ǹ�] 3. �κ��丮[����]" << endl;
	cin >> m_selectNum;
	SetLocation(m_selectNum);
}

void MainGame4::SetShopPage()
{
	while (true) {
		system("cls");
		cout << "===================����===================" << endl;
		cout << "1.�� 2.���� 3.�Ǽ����� 4.����" << endl;
		cout << "=== ���� ȭ������ �������� 0���� ===" << endl;

		cin >> m_selectNum;
		if (m_selectNum == 0) {
			SetMainPage();
			break;
		}
		else {
			SetShopItemPage(m_selectNum);
		}
	}
}

void MainGame4::SetShopItemPage(int itemKind)
{
	int itemCount = 0;
	while (true) {
		system("cls");

		// ���� ���� �������� ���
		/// itemCount ��ȯ�� ������ ���� �־���
		itemCount = m_shop->ItemOutput(itemKind);

		cout << "���� gold : " << m_gold << endl;
		cout << "������ �������� ��ȣ�� �Է�" << endl;
		cout << "itemCount : " << itemCount << endl;
		cout << "===== ���� �޴��� ������ ����ϸ� 0�� =====" << endl;
		cin >> m_selectNum;
		if (m_selectNum == 0)
			break;
		else if ((m_selectNum < 0) || m_selectNum > itemCount) {
			cout << "�߸� �Է�" << endl;
		}
		else {
			tagItemInfo buyItem
				= m_shop->BuyItem(itemKind, m_selectNum, m_gold);
			m_player->AddItem(buyItem);
			Sleep(1000);
		}
	}
}

void MainGame4::SetSellInventoryPage()
{
	int itemCount = 0;
	while (true) {
		system("cls");
		cout << "============= �κ��丮 =============" << endl;
		cout << "���� gold :" << m_gold << endl;
		cout << "�Ǹ��� �������� ��ȣ�� �Է�" << endl;
		cout << "========= ���� ȭ���� 0�� ============" << endl;
	
		itemCount = m_player->ShowInventory();
		
		cin >> m_selectNum;

		if (m_selectNum == 0) {
			SetMainPage();
			break;
		}
		else if ((m_selectNum < 0) || m_selectNum > itemCount) {
			cout << "�߸� �Է�" << endl;
		}
		else {
			m_shop->AddItem(m_player->SellItem(m_selectNum, m_gold));
			Sleep(1000);
		}
	}

}

void MainGame4::SetInventoryPage()
{
	int itemCount = 0;

	while (true) {
		system("cls");
		m_player->ShowStatus();
		cout << "================= �κ��丮 =============== " << endl;
		cout << "������ �������� ��ȣ�� �Է�" << endl;
		cout << "===============����ȭ���� 0��==============" << endl;
		// show inventory
		itemCount = m_player->ShowInventory();

		cin >> m_selectNum;

		if (m_selectNum == 0) {
			SetMainPage();
			break;
		}
		else if ((m_selectNum < 0) || m_selectNum > itemCount) {
			cout << "�߸��� �Է�" << endl;
		}
		else {
			m_player->EquipItem(m_selectNum);
			Sleep(1000);
		}
	}
}

// �ȵǴ� �κ��̶� ���� �κ� ���� �� ��

