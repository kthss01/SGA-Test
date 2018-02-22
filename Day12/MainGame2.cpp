#include "MainGame2.h"



MainGame2::MainGame2()
{
}


MainGame2::~MainGame2()		// �Ҹ���
{
	Release();
}

void MainGame2::Init()		// �ʱ�ȭ�� (�ѹ��� �����)
{
	srand(time(NULL));
	Shuffle(m_card);

	cout << "�÷��̾� ���� �Է� ���ּ��� :";
	cin >> m_playNum;

	// ���� �Ҵ�
	m_player = new tagPlayer[m_playNum];
	
	// Ű���忡 � ���� ���� �ִ� ��� �����ִ� ����
	/// �׶� ������� �Է��ϴ� ������ ������ �ʿ��� ����̶�� ���� �ɵ�
	cin.get();

	for (int i = 0; i < m_playNum; i++) {
		cout << i + 1 << "��° �÷��̾� �̸��� �Է�" << endl;
		// cin.getline() - �������� �Է¹޴� ���� ������
		cin.getline(m_player[i].name, 128);

		m_player[i].bet = 10000;
	}

	m_isBetting = false;
	m_totalBetting = 0;
}

void MainGame2::Release()
{
	// �����Ҵ�� ������ �޸� ������ ���־�� �Ѵ�.
	// ������ ������ ���ᰡ �Ǵ��� 
	// �޸��� ������ �����ϱ� ������ (���� �߻�)
	delete[] m_player;	// �迭�϶� delete�� �迭��
	// �迭 �ƴ� ���� �׳� delete
}

void MainGame2::Update()
{
	system("cls");

	for (int i = 0; i < m_playNum; i++) {
		m_player[i].card1 = m_card[i];
		m_player[i].card2 = m_card[i + m_playNum];
	}

	int selectNum;
	for (int i = 0; i < m_playNum; i++) {
		cout << m_player[i].name << "\t";
		OutCard(m_player[i].card1);
		cout << "\t";
		OutCard(m_player[i].card2);
		cout << "\t";

		m_player[i].jokbo = OutJokbo(
			m_player[i].card1, m_player[i].card2);
		cout << "\t";

		cout << m_player[i].bet << "��" << endl;
			
		if (i == 0) {
			cout << "���� �Ͻðڽ��ϱ� [y(0) / n(1)] : ";
			cin >> selectNum;
			if (selectNum == 1) {
				m_isBetting = false;
				return;
			}
			else {
				m_isBetting = true;
				cout << "���� �ݾ� : ";
				cin >> selectNum;
			}
		}

		// ���� �����ؼ� ���������� ������ ���⼭ ������
		// ���� ����ϱ� ���ؼ� while�� ���������°Ŷ� ���� �κ� ó��
		// -> �ذ�
		m_player[i].bet -= selectNum;
		m_totalBetting += selectNum;
	}
	m_box = JB_0;
	for (int i = 0; i < m_playNum; i++) {
		if (m_box > m_player[i].jokbo) {
			m_box = m_player[i].jokbo;
		}
	}
	for (int i = 0; i < m_playNum; i++) {
		if (m_box == m_player[i].jokbo) {
			cout << m_player[i].name << " �¸�" << endl;
			m_player[i].bet += m_totalBetting;
			Sleep(1000);
		}
	}

	Shuffle(m_card);
	m_totalBetting = 0;
}

JOKBO MainGame2::OutJokbo(CARD card1, CARD card2)
{
	CARD temp;
	// ���� ī����ڰ� card1�� ���� �� swap -> ��� : card1 < card2
	if (card1 > card2) {
		temp = card1;
		card1 = card2;
		card2 = temp;
	}
	if (card1 == CARD_3G && card2 == CARD_8G) {
		cout << "38����";
		return JB_38G;
	}
	else if (card1 == CARD_1G && card2 == CARD_8G) {
		cout << "18����";
		return JB_18G;
	}
	else if (card1 == CARD_1G && card2 == CARD_3G) {
		cout << "13����";
		return JB_13G;
	}
	else if (card1 == CARD_10A && card2 == CARD_10B) {
		cout << "10��";
		return JB_1010;
	}
	else if (card1 == CARD_9A && card2 == CARD_9B) {
		cout << "9��";
		return JB_99;
	}
	else if (card1 == CARD_8G && card2 == CARD_8B) {
		cout << "8��";
		return JB_88;
	}
	else if (card1 == CARD_7A && card2 == CARD_7B) {
		cout << "7��";
		return JB_77;
	}
	else if (card1 == CARD_6A && card2 == CARD_6B) {
		cout << "6��";
		return JB_66;
	}
	else if (card1 == CARD_5A && card2 == CARD_5B) {
		cout << "5��";
		return JB_55;
	}
	else if (card1 == CARD_4A && card2 == CARD_4B) {
		cout << "4��";
		return JB_44;
	}
	else if (card1 == CARD_3G && card2 == CARD_3B) {
		cout << "3��";
		return JB_33;
	}
	else if (card1 == CARD_2A && card2 == CARD_2B) {
		cout << "2��";
		return JB_22;
	}
	else if (card1 == CARD_1G && card2 == CARD_1B) {
		cout << "1��";
		return JB_11;
	}
	else if (
		card1 == CARD_1G && card2 == CARD_2A ||
		card1 == CARD_1G && card2 == CARD_2B ||
		card1 == CARD_2A && card2 == CARD_1B ||
		card1 == CARD_1B && card2 == CARD_2B) {
		cout << "�˸�";
		return JB_12;
	}
	else if (
		card1 == CARD_1G && card2 == CARD_4A ||
		card1 == CARD_1G && card2 == CARD_4B ||
		card1 == CARD_4A && card2 == CARD_1B ||
		card1 == CARD_1B && card2 == CARD_4B) {
		cout << "����";
		return JB_14;
	}
	else if (
		card1 == CARD_1G && card2 == CARD_9A ||
		card1 == CARD_1G && card2 == CARD_9B ||
		card1 == CARD_9A && card2 == CARD_1B ||
		card1 == CARD_1B && card2 == CARD_9B) {
		cout << "����";
		return JB_91;
	}
	else if (
		card1 == CARD_1G && card2 == CARD_10A ||
		card1 == CARD_1G && card2 == CARD_10B ||
		card1 == CARD_10A && card2 == CARD_1B ||
		card1 == CARD_1B && card2 == CARD_10B) {
		cout << "���";
		return JB_101;
	}
	else if (
		card1 == CARD_4A && card2 == CARD_10A ||
		card1 == CARD_4A && card2 == CARD_10B ||
		card1 == CARD_10A && card2 == CARD_4B ||
		card1 == CARD_4B && card2 == CARD_10B) {
		cout << "���";
		return JB_104;
	}
	else if (
		card1 == CARD_4A && card2 == CARD_6A ||
		card1 == CARD_4A && card2 == CARD_6B ||
		card1 == CARD_6A && card2 == CARD_4B ||
		card1 == CARD_4B && card2 == CARD_6B) {
		cout << "����";
		return JB_46;
	}
	else {
		int a, b, c;
		JOKBO jok;
		a = card1 + 1;
		b = card2 + 1;
		jok = JOKBO(JB_0 - (a + b) % 10);
		c = (a + b) % 10;
		switch (c)
		{
		case 9:
			cout << "����";
			break;
		case 0:
			cout << "����";
			break;
		default:
			cout << c << "��";
			break;
		}
		return jok;
	}
}

void MainGame2::OutCard(CARD cardNum)
{
	switch (cardNum) {
	case CARD_1G:
		cout << "1��";
		break;
	case CARD_3G:
		cout << "3��";
		break;
	case CARD_8G:
		cout << "8��";
		break;
	default:
		cout << (cardNum % 10) + 1;
		break;
	}
}

void MainGame2::Shuffle(CARD * card)
{
	int dest, sour;
	CARD temp;

	// ������ �ʱ�ȭ
	for (int i = 0; i < 20; i++) {
		card[i] = CARD(i);
	}

	for (int i = 0; i < 1000; i++) {
		dest = rand() % 20;
		sour = rand() % 20;

		temp = card[dest];
		card[dest] = card[sour];
		card[sour] = temp;
	}
}
