#pragma once

#include "Item.h"

class Inventory
{
protected:
	vector<tagItemInfo> m_vItem;
	vector<tagItemInfo>::iterator m_viItem;

	tagItemInfo m_equipArmor;
	tagItemInfo m_equipWeapon;
public:
	Inventory();
	~Inventory();

	// �κ��丮 ���� �ֱ�
	int ShowInventory();
	// ������ �߰�
	void AddItem(tagItemInfo item);
	// ������ �Ǹ�
	tagItemInfo SellItem(int num, int& gold);

	// ������ ����
	void EquipItem(int num);

	tagItemInfo GetEquipArmor() { return m_equipArmor; }
	void SetEquipArmor(tagItemInfo equipArmor) { 
		m_equipArmor = equipArmor; }

	tagItemInfo GetEquipWeapon() { return m_equipWeapon; }
	void SetEquipWeapon(tagItemInfo equipWeapon) {
		m_equipWeapon = equipWeapon;
	}
};

