#include "Shop.h"



Shop::Shop()
{
}


Shop::~Shop()
{
	
}

/*
	strcat
	strcat_s	// ���� ������� �༮
	strcpy
	strcpy_s	// ���� ������� �༮

	C��� �������� �������־ �Լ� �߰�

	����Ѱ�
	int;
	INT;		// ���� ������� ��
	float;
	FLOAT;		// ���� ������� ��
	bool;
	BOOL;		// ���� ������� ��
	���� ������ ���� : ������ �־ �߰��� �����

	2017 ���� ������ ����ϱ� _s �̰� ����� �����ϴ°� 
	�����ϸ� �̰� ����
*/

void Shop::ItemSetup()
{
	//// ��
	//tagItemInfo item;
	//item.itemKind = ITEM_ARMOR;
	//item.name = "���� ����";
	//item.price = 50;
	//item.attribute = 1;
	//item.description = "�������� ���� ����";
	//item.count = 1;
	//m_vItem.push_back(item);

	//item.itemKind = ITEM_ARMOR;
	//item.name = "�� ����";
	//item.price = 150;
	//item.attribute = 5;
	//item.description = "��� ���� ����";
	//item.count = 1;
	//m_vItem.push_back(item);

	//// ����
	//item.itemKind = ITEM_WEAPON;
	//item.name = "�Ѽհ�";
	//item.price = 100;
	//item.attribute = 5;
	//item.description = "�Ѽ����� �� �� �ִ� ��";
	//item.count = 1;
	//m_vItem.push_back(item);

	//item.itemKind = ITEM_WEAPON;
	//item.name = "������";
	//item.price = 250;
	//item.attribute = 15;
	//item.description = "��ȭ ��Ÿ���� ������";
	//item.count = 1;
	//m_vItem.push_back(item);

	tagItemInfo item;

	FILE* fp;
	fopen_s(&fp, "Text/Item.txt", "r");	// ���ϰ�� ������Ʈ ���� �����
	// s�� safe �ǹ�
	// �����η� ��� ��
	//fopen_s(&fp, "C:/Users/kthss/source/repos/���� ��ī����/Day15/Text/Item.txt", "r");

	char* str = new char[1024]; // �ڸ� ������ ������ �༮
	memset(str, 0, 1024); // memset �ʱ�ȭ ���ִ� �Լ�, 0���� 1024��ŭ �ʱ�ȭ
	// ������ ������ ���� �ƴ� ������ �аڴ�
	// feof(fp) �������̸� true �ƴϸ� false ��ȯ
	while (!feof(fp)) {
		// ���پ� ���� ���� ������ ���� ���� �� �ʱ�ȭ
		char* szBuff = new char[1024];
		memset(szBuff, 0, 1024);
		fgets(szBuff, 1024, fp);

		// ���� ó�� ���ڿ��� ���̰� 0�̸� ��� ����
		// ���� �ȿ� ���ͷ� ���������� (���� ó��)
		if (strlen(szBuff) == 0)
			continue;

		// szBuff = [1][�ʺ��� �ǻ�][50][2][���� ������][2]
		// str = "1"(���ڿ�)
		//str = strtok(szBuff, "[]");
		str = strtok_s(szBuff, "[]", &szBuff);	// �ڸ� ���ڿ�, �ڸ� ����, �ڸ��� �� �༮�� ��������

		item.itemKind = (ITEM)atoi(str);	// atoi ���ڿ� -> ������ �ٲ���
		// �ݴ��� ���� -> ���ڿ� : itoa

		// �ѹ� �ڸ� �༮�� ��� �ڸ����� NULL �־��־����
		// strtok�� str ������ ��� 1�� ����

		// szbuff = �ʺ��� �ǻ�][50][2][���� ������][2]
		// str = "�ʺ��� �ǻ�"
		//str = strtok(NULL, "[]");
		str = strtok_s(szBuff, "[]", &szBuff);
		item.name = str;

		// szbuff = 50][2][���� ������][2]
		// str = "50"
		//str = strtok(NULL, "[]");
		str = strtok_s(szBuff, "[]", &szBuff);
		item.price = atoi(str);

		// szbuff = 2][���� ������][2]
		// str = "2"
		//str = strtok(NULL, "[]");
		str = strtok_s(szBuff, "[]", &szBuff);
		item.attribute = atoi(str);

		// szbuff = ���� ������][2]
		// str = "���� ������"
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

int Shop::ItemOutput(int num)	// Inventory.cpp ShowInventory() �� ����
{
	int itemCount = 0;
	m_viItem = m_vItem.begin();
	for (m_viItem; m_viItem != m_vItem.end(); ++m_viItem) {
		// ���� ������ ������ ������ ���
		if (m_viItem->itemKind != num) continue;
		// i++ (����ϰ� ����), ++i(�����ǰ� ���) ������
		// ���� �����ϳ� ����
		cout << "==================================" << endl;
		cout << "������ ��ȣ : " << ++itemCount << endl;
		cout << "�̸� : " << m_viItem->name << endl;
		cout << "���� : " << m_viItem->price << endl;
		cout << "�ɷ�ġ : " << m_viItem->attribute << endl;
		cout << "���� : " << m_viItem->description << endl;
		cout << "���� : ";
		// ���� ������ (����) ? �� : ����
		(m_viItem->count > 0) 
			? cout << m_viItem->count << endl
			: cout << "����" << endl;
		cout << "==================================" << endl;
	}
	return itemCount;
}

tagItemInfo Shop::BuyItem(int itemKind, int num, int & gold)
{
	tagItemInfo buyItem;
	buyItem.itemKind = ITEM_EMPTY;
	int itemCount = 0;	// ȭ�鿡 ��µǾ��� �� ������ ��ȣ �ǹ�
	m_viItem = m_vItem.begin();
	for (m_viItem; m_viItem != m_vItem.end(); ++m_viItem) {
		// ���� ������ �����۸� ���
		if (m_viItem->itemKind != itemKind) continue;

		// ���� ������ ��ȣ�� ���� ��
		if (++itemCount == num) {
			// ������ ���� ���� ��
			if (gold >= m_viItem->price) {
				// ������ ������ ������ �������� ��
				if (m_viItem->count > 0) {
					cout << m_viItem->name << "�� "
						<< m_viItem->price << "gold�� ����" << endl;
					gold -= m_viItem->price;
					m_viItem->count--;
					buyItem = *m_viItem;	// �������� ���� �־���
				}
				else {
					cout << "��� ����" << endl;
				}
			}
			else {
				cout << "���� ����" << endl;
			}
			// ������ ã�����Ƿ� ��
			break;
		}
	}
	return buyItem;
}

void Shop::AddItem(tagItemInfo item) // Inventory.cpp AddItem() ����
{
	bool isNewItem = true;

	m_viItem = m_vItem.begin();
	for (m_viItem; m_viItem != m_vItem.end(); ++m_viItem) {
		// ������ ���� �������� Ȯ��
		if (m_viItem->itemKind != item.itemKind) continue;

		// strcmp ���� string �ȿ� compare �Լ� ����
		// ������ �̸� ������ ������ ����
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


