#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

void temp(int a) {
	for (int i = 0; i < 10; i++)
		cout << a << "��° �Լ� " << i << " ����" << endl;
}

void main() {
	// �׳� ���������� ����
	//temp(1);
	//temp(2);

	std::thread th1 = thread(temp, 1);
	std::thread th2 = thread(temp, 2);

	th1.join();
	th2.join();
}