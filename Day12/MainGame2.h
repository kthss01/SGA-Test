#pragma once
#include <iostream>
#include <time.h>
#include <Windows.h>
using namespace std;

/// ������ Ȱ�� ������ �� ������ �ְ� ���ϰ� �ۼ� ����

// ī��
enum CARD {
	CARD_1G, CARD_2A, CARD_3G, CARD_4A, CARD_5A,
	CARD_6A, CARD_7A, CARD_8G, CARD_9A, CARD_10A,
	CARD_1B, CARD_2B, CARD_3B, CARD_4B, CARD_5B,
	CARD_6B, CARD_7B, CARD_8B, CARD_9B, CARD_10B,
};

// ����
// ���������� �̰� �� ���� ������ ���� ����� �������� ���ڷ� �����ϴ°�
enum JOKBO {
	JB_38G, JB_18G, JB_13G, JB_1010, JB_99, JB_88,
	JB_77, JB_66, JB_55, JB_44, JB_33, JB_22, JB_11,
	JB_12, JB_14, JB_91, JB_101, JB_104, JB_46, JB_9,
	JB_8, JB_7, JB_6, JB_5, JB_4, JB_3, JB_2, JB_1, JB_0
};

// �÷��̾� ����ü
struct tagPlayer {
	char name[128];
	CARD card1, card2;
	JOKBO jokbo;
	int bet;
};

/// Ŭ���� �̸� �ߺ��Ǽ� ������� �ȸ�������°� ����
class MainGame2
{
private:
	CARD m_card[20];
	tagPlayer* m_player;
	int m_playNum;
	int m_box;			// ���� �¸��ڸ� ����

	bool m_isBetting;
	int m_totalBetting;
	
public:
	MainGame2();
	~MainGame2();

	void Init();		// �ʱ�ȭ��
	void Release();		// ������
	void Update();		// ȭ�� ��� �� �����÷���

	JOKBO OutJokbo(CARD card1, CARD card2);
	void OutCard(CARD cardNum);		// ī�� ���
	void Shuffle(CARD* card);

	bool GetIsBetting() {
		return m_isBetting;
	}
};

