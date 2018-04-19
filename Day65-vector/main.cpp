#include <iostream>
#include <vector>

using namespace std;

int main() {
	vector<int> vNum;

	for (int i = 0; i < 10000; i++)
		vNum.push_back(i);

	cout << "size : " << vNum.size() << endl;
	cout << "capacity : " << vNum.capacity() << endl;

	vector<int> vNum2;
	vNum2.resize(10000);

	for (int i = 0; i < 10000; i++)
		vNum2[i] = i;

	cout << "size : " << vNum2.size() << endl;
	cout << "capacity : " << vNum2.capacity() << endl;

	return 0;
}