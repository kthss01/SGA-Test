// iterator -> smart potiner
// stl : vector, map

#include <iostream>
#include <vector>
// �ֱ� �ѵ� ��������� ���� �ʰ� ���� ���� ��찡 ����
#include <list>
#include <map>

using namespace std;

int main() {

	//int * num = new int[20];
	//for (int i = 0; i < 20; i++)
	//	num[i] = i;

	//// �ּҰ� �̿� ���
	//for (int i = 0; i < 20; i++)
	//	cout << *(num + i) << endl;

	//// �迭 ��ȣ�� ���
	//for (int i = 0; i < 20; i++)
	//	cout << num[i] << endl;

	//delete[] num;

	//vector<int> num;

	//for (int i = 0; i < 20; i++) {
	//	num.push_back(i);
	//}

	//// vector �迭ó�� ��ȣ�� ���
	//for (int i = 0; i < 20; i++) {
	//	cout << num[i] << endl;
	//}

	//// �׳� �������� �ٸ� vector�� begin �־ ���� ���ư�
	//vector<int>::iterator viNum;

	//viNum = num.begin();
	//// end() ������ ���� 
	//// end() �� ���� �ƴ϶� ������ ���� ��
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
	// // �̷����ϸ� ���� ���� �ּҰ��ִ°Ŷ�
	//	num.push_back(make_pair(str, 1));		
	//}

	//for (int i = 0; i < 10; i++) {
	//	cout << num[i].first << endl;
	//	cout << num[i].second << endl;
	//}

	return 0;
}