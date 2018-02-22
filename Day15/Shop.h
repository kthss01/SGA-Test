#pragma once

#include "Item.h"

class Shop
{
private:
	// 구조체를 담은 벡터
	vector<tagItemInfo> m_vItem;
	vector<tagItemInfo>::iterator m_viItem;	
	// STL 사용시 iterator 만들어주면 좋다

public:
	Shop();
	~Shop();

	// 초기 아이템 셋팅
	void ItemSetup();
	// 아이템 출력
	int ItemOutput(int num);
	// 상점 아이템 구입
	tagItemInfo BuyItem(int itemKind, int num, int& gold);
	// 상점에 아이템 추가
	void AddItem(tagItemInfo item);
};

