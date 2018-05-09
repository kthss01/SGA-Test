#pragma once

#include <iostream>
using namespace std;

class Node
{
private:
	int data;
	Node* pNext;
public:
	Node();
	Node(int data, Node* pNext = NULL);
	~Node();

	// ��� ���� ���̴°� 
	void AddNode(Node* pNext);
	// �߰� ���� (���°)
	void AddNode(int count, Node* pNode);

	// ��� �� ����� �Լ�
	void Delete();
	// �߰� ���� (���� data or ���°)
	void Delete(int data, Node** ppThis);

	void Print();
	// ������ (������)
	void Reverse(Node* pPrev);
	// ���������� ������ ��带 ���� �־����
	Node* GetTail();
};

/*
	����
	�߰� ���� (���°�� ������)
	�߰� ���� (���� �����ϰ� ���� ���� ������ or ���° ��� ����)
	������ (������)
	ex) 1 2 3 -> 3 2 1

	Node �� SLL Ŭ���� �ƹ����� ���� �ڵ� ����

	reverse �� ����� Next �� ���� ���� ��� ����Ű�� ������ �����ϸ� �ɵ�
*/

