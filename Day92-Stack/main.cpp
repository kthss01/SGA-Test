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

	// 음수일 경우도 있어서
	if (sToken[nIndex] == '-') {
		if (sToken[nIndex - 1] == '(') 
			return false;

		return true;
	}

	return false;
}

string GetToken(string infix, int& index) {
	// 생성자로 string 초기화 해줘도 됨
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
	과제
	환형 큐 만들기
	큐 출력은
	비어잇는지 몇퍼센트 차있는지 등 출력하기
	
	바이너리 서치 트리 출력
	랜덤한 숫자 여러개 트리에 넣어두고
	제일 작은 숫자부터 큰 숫자 순으로 출력
	트리 삭제 -> 트리 구조 무너뜨리지 않고 올리는 방법으로 올리면 됨
	찾는 함수도 만들기
	검색은 3가지로 나눠짐
	큰수에서부터, 작은수에서부터, 너비값에서부터 찾는거로 나눠짐

	트리 레드 블랙 임 -> 한번 읽어보는게 좋음 이거 구현하느니 맵을 쓰는게 나음
	stl 맵이 레드 블랙 트리로 만들어져 있음
	하나는 레드 하나는 블랙으로 계산해서 넣을 때마다 균등하게 트리 잡아주는거
*/