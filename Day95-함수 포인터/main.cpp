#include <Windows.h>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

void Move() {
	printf("이동 \n");
}

void MoveRight() {
	printf("오른쪽 이동 \n");
}

void MoveLeft() {
	printf("왼쪽 이동 \n");
}

string Print(int direction) {
	string str = "이동 방향 " + to_string(direction);

	return str;
}

int main() {
	//void(*func)();

	//func = Move;
	//func();

	//func = MoveRight;
	//func();

	void(*arr[2])();
	arr[0] = MoveLeft;
	arr[1] = MoveRight;

	vector<void(*)()> vec;
	vec.push_back(MoveLeft);
	vec.push_back(MoveRight);

	string(*ptr)(int) = Print;

	int direction = -1;
	
	while (true) {
		direction = -1;
		if (GetAsyncKeyState(VK_LEFT) & 0x8000 == 0x8000)
			direction = 0;
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000 == 0x8000)
			direction = 1;

		if (direction > -1) {
			vec[direction]();

			string str = ptr(direction);
			printf("%s\n", str.c_str());
		}
	}

	return 0;
}