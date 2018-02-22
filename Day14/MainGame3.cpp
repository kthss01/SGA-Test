#include "MainGame3.h"

// emplace back���� ���� �������� �߰��ϴ� ��� , emplace - ��ġ�ϴ�

MainGame3::MainGame3()
{
	// ���� �߰� ���
	// push_back();

	for (int i = 0; i < 10; i++) {
		//cout << "capacity: " << m_vNumber.capacity() << endl;
		//// �̸� ���� Ȯ�� ���� capacity / 2 ��ŭ ���� 4 -> 6 , 6 -> 9 , 9 -> 13
		//// �޸� ���� �־ ������ �Ƚ����� ������ �޸𸮰� Ŀ�� �����ϰ� �Ѿ
		//cout << "size: " << m_vNumber.size() << endl;

		m_vNumber.push_back(i + 1);
	}

	// ����	(�� �ڿ������� �����ȴ�.)
	m_vNumber.pop_back();

	/*
		begin() => �迭�� 0�� �ε��� (ù��° �ε���)
		end()	=> ������ �ε��� (������ ������ ��, NULL�� �������)
		insert(�迭�� ��ġ(�ε���), ��) => �� �߰�
		insert(�迭�� ��ġ(�ε���), ����, ��) => ������ŭ �� �߰�
		erase(�迭�� ��ġ ����)
		clear() �迭 ���� ����
	*/
	//m_vNumber.erase(m_vNumber.begin() + 3);
	//m_vNumber.insert(m_vNumber.end() - 2, 200);
	//m_vNumber.insert(m_vNumber.begin(), 3, 100);

	//cout << m_vNumber.size() << " " << m_vNumber.capacity() << endl;

	//m_vNumber.clear();

	//m_vNumber.resize(ũ��) ũ�� ������
	//m_vNumber.at(�ε��� ��ȣ) �ε��� ��ȣ ��° �� ȣ��
	//m_vNumber.empty() ���� �� �ִ��� Ȯ��
	//m_vNumber.capacity() ���Ͱ� ���� �ϰ� �ִ� ���� �޸� ������ ������ ����

	// ���
	//for (int i = 0; i < m_vNumber.size(); i++) {
	//	cout << m_vNumber[i] << endl;
	//}

	//m_viNumber = m_vNumber.begin();
	//for (m_viNumber; m_viNumber != m_vNumber.end(); ++m_viNumber) {
	//	cout << *m_viNumber << endl;
	//}

	// c++11 ���� ������ �༮	
	// c++ foreach ���̶�� ���� �ɵ�, foreach���� c++ ����
	// ���� i�� �����ص� �ݿ� �ȵ�
	for (int i : m_vNumber) {
		cout << i << endl;
	}

	for (int i = 0; i < 10; i++) {
		tagPlayer player;
		player.hp = 100;
		player.mp = 100;
		player.etc = 0.0f + i;

		m_vPlayer.push_back(player);
	}

	for (tagPlayer player : m_vPlayer) {
		cout << player.etc << "��° �÷��̾��� HP : " 
			<< player.hp << " MP : " << player.mp << endl;
	}
}


MainGame3::~MainGame3()
{
}
