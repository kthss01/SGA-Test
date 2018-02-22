#include "MainGame2.h"



MainGame2::MainGame2()
{
}


MainGame2::~MainGame2()		// 소멸자
{
	Release();
}

void MainGame2::Init()		// 초기화용 (한번만 실행됨)
{
	srand(time(NULL));
	Shuffle(m_card);

	cout << "플레이어 수를 입력 해주세요 :";
	cin >> m_playNum;

	// 동적 할당
	m_player = new tagPlayer[m_playNum];
	
	// 키보드에 어떤 값이 남아 있는 경우 지워주는 역할
	/// 그때 빙고게임 입력하다 끝나던 문제에 필요한 기능이라고 보면 될듯
	cin.get();

	for (int i = 0; i < m_playNum; i++) {
		cout << i + 1 << "번째 플레이어 이름을 입력" << endl;
		// cin.getline() - 라인으로 입력받는 엔터 전까지
		cin.getline(m_player[i].name, 128);

		m_player[i].bet = 10000;
	}

	m_isBetting = false;
	m_totalBetting = 0;
}

void MainGame2::Release()
{
	// 동적할당시 무조건 메모리 해제도 해주어야 한다.
	// 이유는 실행이 종료가 되더라도 
	// 메모리의 공간을 차지하기 때문에 (누수 발생)
	delete[] m_player;	// 배열일땐 delete도 배열로
	// 배열 아닌 경우는 그냥 delete
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

		cout << m_player[i].bet << "원" << endl;
			
		if (i == 0) {
			cout << "배팅 하시겠습니까 [y(0) / n(1)] : ";
			cin >> selectNum;
			if (selectNum == 1) {
				m_isBetting = false;
				return;
			}
			else {
				m_isBetting = true;
				cout << "배팅 금액 : ";
				cin >> selectNum;
			}
		}

		// 조금 보강해서 마무리하자 수업은 여기서 끝났음
		// 배팅 계속하기 위해서 while문 빠져나오는거랑 여기 부분 처리
		// -> 해결
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
			cout << m_player[i].name << " 승리" << endl;
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
	// 작은 카드숫자가 card1로 오게 끔 swap -> 결론 : card1 < card2
	if (card1 > card2) {
		temp = card1;
		card1 = card2;
		card2 = temp;
	}
	if (card1 == CARD_3G && card2 == CARD_8G) {
		cout << "38광땡";
		return JB_38G;
	}
	else if (card1 == CARD_1G && card2 == CARD_8G) {
		cout << "18광땡";
		return JB_18G;
	}
	else if (card1 == CARD_1G && card2 == CARD_3G) {
		cout << "13광땡";
		return JB_13G;
	}
	else if (card1 == CARD_10A && card2 == CARD_10B) {
		cout << "10땡";
		return JB_1010;
	}
	else if (card1 == CARD_9A && card2 == CARD_9B) {
		cout << "9땡";
		return JB_99;
	}
	else if (card1 == CARD_8G && card2 == CARD_8B) {
		cout << "8땡";
		return JB_88;
	}
	else if (card1 == CARD_7A && card2 == CARD_7B) {
		cout << "7땡";
		return JB_77;
	}
	else if (card1 == CARD_6A && card2 == CARD_6B) {
		cout << "6땡";
		return JB_66;
	}
	else if (card1 == CARD_5A && card2 == CARD_5B) {
		cout << "5땡";
		return JB_55;
	}
	else if (card1 == CARD_4A && card2 == CARD_4B) {
		cout << "4땡";
		return JB_44;
	}
	else if (card1 == CARD_3G && card2 == CARD_3B) {
		cout << "3땡";
		return JB_33;
	}
	else if (card1 == CARD_2A && card2 == CARD_2B) {
		cout << "2땡";
		return JB_22;
	}
	else if (card1 == CARD_1G && card2 == CARD_1B) {
		cout << "1땡";
		return JB_11;
	}
	else if (
		card1 == CARD_1G && card2 == CARD_2A ||
		card1 == CARD_1G && card2 == CARD_2B ||
		card1 == CARD_2A && card2 == CARD_1B ||
		card1 == CARD_1B && card2 == CARD_2B) {
		cout << "알리";
		return JB_12;
	}
	else if (
		card1 == CARD_1G && card2 == CARD_4A ||
		card1 == CARD_1G && card2 == CARD_4B ||
		card1 == CARD_4A && card2 == CARD_1B ||
		card1 == CARD_1B && card2 == CARD_4B) {
		cout << "독사";
		return JB_14;
	}
	else if (
		card1 == CARD_1G && card2 == CARD_9A ||
		card1 == CARD_1G && card2 == CARD_9B ||
		card1 == CARD_9A && card2 == CARD_1B ||
		card1 == CARD_1B && card2 == CARD_9B) {
		cout << "구삥";
		return JB_91;
	}
	else if (
		card1 == CARD_1G && card2 == CARD_10A ||
		card1 == CARD_1G && card2 == CARD_10B ||
		card1 == CARD_10A && card2 == CARD_1B ||
		card1 == CARD_1B && card2 == CARD_10B) {
		cout << "장삥";
		return JB_101;
	}
	else if (
		card1 == CARD_4A && card2 == CARD_10A ||
		card1 == CARD_4A && card2 == CARD_10B ||
		card1 == CARD_10A && card2 == CARD_4B ||
		card1 == CARD_4B && card2 == CARD_10B) {
		cout << "장사";
		return JB_104;
	}
	else if (
		card1 == CARD_4A && card2 == CARD_6A ||
		card1 == CARD_4A && card2 == CARD_6B ||
		card1 == CARD_6A && card2 == CARD_4B ||
		card1 == CARD_4B && card2 == CARD_6B) {
		cout << "세륙";
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
			cout << "갑오";
			break;
		case 0:
			cout << "망통";
			break;
		default:
			cout << c << "끗";
			break;
		}
		return jok;
	}
}

void MainGame2::OutCard(CARD cardNum)
{
	switch (cardNum) {
	case CARD_1G:
		cout << "1광";
		break;
	case CARD_3G:
		cout << "3광";
		break;
	case CARD_8G:
		cout << "8광";
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

	// 열거형 초기화
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
