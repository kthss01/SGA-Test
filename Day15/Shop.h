#pragma once

#include "Item.h"

class Shop
{
private:
	// ����ü�� ���� ����
	vector<tagItemInfo> m_vItem;
	vector<tagItemInfo>::iterator m_viItem;	
	// STL ���� iterator ������ָ� ����

public:
	Shop();
	~Shop();

	// �ʱ� ������ ����
	void ItemSetup();
	// ������ ���
	int ItemOutput(int num);
	// ���� ������ ����
	tagItemInfo BuyItem(int itemKind, int num, int& gold);
	// ������ ������ �߰�
	void AddItem(tagItemInfo item);
};

