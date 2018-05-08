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
	// ��� �� ����� �Լ�
	void Delete();
	void Print();
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

