#include "Map.h"



Map::Map()
{
	// �ʿ� �߰��ϴ� ���

	// .insert() �ʿ� �߰�
	pair<char*, int> pt1("���̽�", 150);
	m_mNumber.insert(pt1);

	char* str = "���̾��";
	m_mNumber.insert(make_pair(str, 100));

	str = "��Ʈ";
	m_mNumber[str] = 50;	// �� ������� �ʱ�ȭ�ϴ°� ��õ x	
	// �ڷ��� Ȯ���ϰ� �ִ°� ����

	//str = "���̽�";
	//m_mNumber.erase(str);	// Ű ������ ����

	//// Ű������ Ư�� ���� ã�´�. �˻�
	//// end() ���� null �������
	//if (m_mNumber.find(str) != m_mNumber.end()) {
	//	cout << "�ִ�" << endl;
	//}
	//else {
	//	cout << "����" << endl;
	//}

	// �ݺ��ڸ� �̿��ؼ� ���
	m_miNumber = m_mNumber.begin();
	for (m_miNumber; m_miNumber != m_mNumber.end(); ++m_miNumber) {
		cout << m_miNumber->first << "," 
			<< m_miNumber->second << endl;
	}
}


Map::~Map()
{
}
