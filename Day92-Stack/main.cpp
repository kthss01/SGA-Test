#include "Stack.h"

#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>

using namespace std;

bool IsOperator(string sToken) {
	if (sToken == "*" ||
		sToken == "/" ||
		sToken == "+" ||
		sToken == "-" ||
		sToken == "(" ||
		sToken == ")") 
		return true;

	return false;
}

bool IsOperator(string sToken, int& nIndex) {
	if (sToken[nIndex] == '*' ||
		sToken[nIndex] == '/' ||
		sToken[nIndex] == '+' ||
		sToken[nIndex] == '(' ||
		sToken[nIndex] == ')') 
		return true;

	// ������ ��쵵 �־
	if (sToken[nIndex] == '-') {
		if (sToken[nIndex - 1] == '(') 
			return false;

		return true;
	}

	return false;
}

string GetToken(string infix, int& index) {
	// �����ڷ� string �ʱ�ȭ ���൵ ��
	string sToken("");

	while (index < infix.length()) {
		if (IsOperator(infix, index)) {
			if (sToken.length() == 0) {
				sToken += infix[index++];
			}
			break;
		}
		else {
			sToken += infix[index++];
		}
	}

	return sToken;
}

int OperatorPriority(string sOperator) {
	if (sOperator == "*" || sOperator == "/") return 3;
	if (sOperator == "+" || sOperator == "-") return 2;
	if (sOperator == "(") return 1;
}

int main() {
	cStack<string> stkOperator;
	vector<string> postfix;

	FILE* fp = NULL;
	fopen_s(&fp, "data.txt", "r");
	char szBuf[1024];
	fgets(szBuf, 1024, fp);

	string infix(szBuf);
	
	cout << infix << endl;
	
	infix = "(" + infix + ")";

	fclose(fp);

	int index = 0;

	while (true) {
		string token = GetToken(infix, index);
		if (token.length() == 0) break;

		if (IsOperator(token)) {
			if (token == "(") {
				stkOperator.Push(token);
			}
			else if (token == ")") {
				while (true) {
					string top = stkOperator.Pop();
					if (top == "(") break;
					postfix.push_back(top);
				}
			}
			else {
				while (true) {
					string top = stkOperator.Top();
					if (OperatorPriority(top)
						< OperatorPriority(token))
						break;
					postfix.push_back(stkOperator.Pop());
				}
				stkOperator.Push(token);
			}
		}
		else {
			postfix.push_back(token);
		}
	}

	while (!stkOperator.IsEmpty()) {
		postfix.push_back(stkOperator.Pop());
	}

	for (int i = 0; i < postfix.size(); i++)
		cout << postfix[i];
	cout << endl;

	cStack<float> stkOperand;

	for (string s : postfix) {
		if (IsOperator(s)) {
			float f2 = stkOperand.Pop();
			float f1 = stkOperand.Pop();
			
			if (s == "+") stkOperand.Push(f1 + f2);
			else if (s == "-") stkOperand.Push(f1 - f2);
			else if (s == "*") stkOperand.Push(f1 * f2);
			else if (s == "/") stkOperand.Push(f1 / f2);
		}
		else {
			stkOperand.Push((float)atof(s.c_str()));
		}
	}

	cout << stkOperand.Pop() << endl;

	assert(stkOperand.IsEmpty());

	return 0;
}

/*
	����
	ȯ�� ť �����
	ť �����
	����մ��� ���ۼ�Ʈ ���ִ��� �� ����ϱ�
	
	���̳ʸ� ��ġ Ʈ�� ���
	������ ���� ������ Ʈ���� �־�ΰ�
	���� ���� ���ں��� ū ���� ������ ���
	Ʈ�� ���� -> Ʈ�� ���� ���ʶ߸��� �ʰ� �ø��� ������� �ø��� ��
	ã�� �Լ��� �����
	�˻��� 3������ ������
	ū����������, ��������������, �ʺ񰪿������� ã�°ŷ� ������

	Ʈ�� ���� �� �� -> �ѹ� �о�°� ���� �̰� �����ϴ��� ���� ���°� ����
	stl ���� ���� �� Ʈ���� ������� ����
	�ϳ��� ���� �ϳ��� ������ ����ؼ� ���� ������ �յ��ϰ� Ʈ�� ����ִ°�
*/