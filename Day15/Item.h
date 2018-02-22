#pragma once
// Item.h

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// �������� ����
enum ITEM {
	ITEM_EMPTY,		// ������ ����
	ITEM_ARMOR,	// ��
	ITEM_WEAPON,	// ����
	ITEM_RING,		// ����
	ITEM_POTION,	// ����
	ITEM_SOLDOUT	// �Ǹ� �Ϸ�
};

// ������ ���� ���� ����ü
struct tagItemInfo {
	ITEM itemKind;		// �������� ����
	string name;		// �������� �̸�
	string description;	// �������� ����
	int attribute;		// �������� Ư��
	int price;			// ������ ����
	int count;			// ������ ����
};