#include "Inventory.h"



Inventory::Inventory()
{
	tagItemInfo itemEmpty = { ITEM_EMPTY, "", "",0,0,0 };
	m_equipArmor = itemEmpty;
	m_equipWeapon = itemEmpty;
}


Inventory::~Inventory()
{
}

int Inventory::ShowInventory()
{
	int itemCount = 0;
	m_viItem = m_vItem.begin();
	for (m_viItem; m_viItem != m_vItem.end(); ++m_viItem) {
		// i++ (����ϰ� ����), ++i(�����ǰ� ���) ������
		// ���� �����ϳ� ����
		cout << "==================================" << endl;
		cout << "������ ��ȣ : " << ++itemCount << endl;
		cout << "�̸� : " << m_viItem->name << endl;
		cout << "���� : " << m_viItem->price << endl;
		cout << "�ɷ�ġ : " << m_viItem->attribute << endl;
		cout << "���� : " << m_viItem->description << endl;
		cout << "==================================" << endl;
	}
	return itemCount;
}

void Inventory::AddItem(tagItemInfo item)
{
	// �������� �����ϱ⸸ �ϸ� �ֱ�
	if (item.itemKind != ITEM_EMPTY) {
		m_vItem.push_back(item);
	}
}

tagItemInfo Inventory::SellItem(int num, int & gold)
{
	// �κ����� �Ǹ� ������ ����
	tagItemInfo sellItem;
	m_viItem = m_vItem.begin() + (num - 1);
	sellItem = *m_viItem;
	m_vItem.erase(m_viItem);	// erase�õ� iterator�� ������

	// �Ǹ� �ݾ�
	int sellPrice = sellItem.price / 2;
	cout << sellItem.name << "�� " << sellPrice << "gold�� �Ǹ�" << endl;
	gold += sellPrice;

	return sellItem;
}

// ������ ����
void Inventory::EquipItem(int num)
{
	tagItemInfo beforeItem;
	m_viItem = m_vItem.begin() + (num - 1);

	switch (m_viItem->itemKind)
	{
	case ITEM_ARMOR:
		beforeItem = GetEquipArmor();
		SetEquipArmor(*m_viItem);
		m_vItem.erase(m_viItem);

		if (beforeItem.itemKind == ITEM_ARMOR) {
			m_vItem.push_back(beforeItem);
		}

		break;
	case ITEM_WEAPON:
		beforeItem = GetEquipWeapon();
		SetEquipWeapon(*m_viItem);
		m_vItem.erase(m_viItem);

		if (beforeItem.itemKind == ITEM_WEAPON) {
			m_vItem.push_back(beforeItem);
		}

		break;
	default:
		break;
	}
}
