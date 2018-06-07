#include <stdio.h>
#include <string>
#include <vector>
#include <functional>	// function �̶�� �ϴ� template�̶�� �ϸ��
using namespace std;

void Move() {
	printf("�̵�\n");
}

class Test {
public:
	static void Temp() {
		printf("Test::Temp\n");
	}
	void Temp2() {
		printf("Test::Temp2\n");
	}
	void Temp3(int a, int b) {
		printf("%d, %d\n", a, b);
	}
	string Temp4(string str, int a, int b) {
		str += " " + to_string(a) + " " + to_string(b);
		return str;
	}

	int number = 0;
	void Temp5() {
		printf("Test::Temp : %d\n", number);
	}
};

class Test2 {
public:
	void Render() {
		printf("Test2::Render\n");
	}
};

int main() {
	function<void(void)> f;
	// �������ִ°�
	f = bind(Move);
	//f();

	vector<function<void(void)>> vec;
	vec.push_back(bind(Move));
	vec.push_back(bind(Test::Temp));

	Test* ob = new Test;
	vec.push_back(bind(&Test::Temp2,ob));

	for (int i = 0; i < vec.size(); i++) {
		vec[i]();
	}

	function<void(int, int)> func;
	// placeholders ������ �������ִ°�
	// �̸� ���� �־��൵ �� �� ������ ������
	// bind ���� �������� ���� �������� ���� ������ �� ���� (�����ϴ� �� ����)
	func = bind(&Test::Temp3, ob, placeholders::_1, placeholders::_2);
	func = bind(&Test::Temp3, ob, 100, placeholders::_2);
	func(50, 200);
	
#define P placeholders

	function<string(string, int, int)> func2;
	func2 = bind(&Test::Temp4, ob, P::_1, P::_2, P::_3);

	string temp = func2("�ĺ��� :", 20, 40);

	printf("%s\n", temp.c_str());


	vector < function<void(void)>> vecRender;
	Test* ob2 = new Test;

	Test2* ob3 = new Test2;

	vecRender.push_back(bind(ob->Temp));
	vecRender.push_back(bind(ob2->Temp));
	vecRender.push_back(bind(&Test2::Render, ob3));

	for (int i = 0; i < vecRender.size(); i++)
		vecRender[i]();

	delete ob;
	delete ob2;
	delete ob3;
	return 0;
}