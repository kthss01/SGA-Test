#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

void temp(int a) {
	for (int i = 0; i < 10; i++)
		cout << a << "번째 함수 " << i << " 실행" << endl;
}

void main() {
	// 그냥 순차적으로 진행
	//temp(1);
	//temp(2);

	std::thread th1 = thread(temp, 1);
	std::thread th2 = thread(temp, 2);

	th1.join();
	th2.join();
}