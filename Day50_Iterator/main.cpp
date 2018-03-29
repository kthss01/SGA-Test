// iterator -> smart potiner
// stl : vector, map

#include <iostream>
#include <vector>
// 있긴 한데 만들어진걸 쓰진 않고 만들어서 쓰는 경우가 많음
#include <list>
#include <map>

using namespace std;

int main() {

	//int * num = new int[20];
	//for (int i = 0; i < 20; i++)
	//	num[i] = i;

	//// 주소값 이용 출력
	//for (int i = 0; i < 20; i++)
	//	cout << *(num + i) << endl;

	//// 배열 번호로 출력
	//for (int i = 0; i < 20; i++)
	//	cout << num[i] << endl;

	//delete[] num;

	//vector<int> num;

	//for (int i = 0; i < 20; i++) {
	//	num.push_back(i);
	//}

	//// vector 배열처럼 번호로 출력
	//for (int i = 0; i < 20; i++) {
	//	cout << num[i] << endl;
	//}

	//// 그냥 포인터임 다른 vector의 begin 넣어도 같이 돌아감
	//vector<int>::iterator viNum;

	//viNum = num.begin();
	//// end() 넣으면 터짐 
	//// end() 는 끝이 아니라 쓰레기 값이 들어감
	////viNum = num.end();

	////cout << "vNum : " << num[0] << endl;
	////cout << "viNum : " << *viNum << endl;

	//for (viNum; viNum != num.end(); ++viNum) {
	//	cout << *viNum << endl;
	//}

	//map<char*, int> mNum;

	//mNum.insert(make_pair<char*, int>((char*)"Test", 1));
	//pair<char*, int> add = make_pair((char*)"Test2", 1);
	//mNum.insert(make_pair((char*)"Test", 1));
	//mNum.insert(add);

	//vector< pair<char*, int> > num;

	//char str[128];
	//for (int i = 0; i < 10; i++) {
	//	sprintf_s(str, "Test%d", i);
	// // 이렇게하면 문제 있음 주소값넣는거라
	//	num.push_back(make_pair(str, 1));		
	//}

	//for (int i = 0; i < 10; i++) {
	//	cout << num[i].first << endl;
	//	cout << num[i].second << endl;
	//}

	return 0;
}