#include <iostream>
#include <time.h>

using namespace std;

void main() {
	srand(time(NULL));

	int selectNumber;
	int comNumber;

	int winCount = 0;
	int loseCount = 0;

	for (int i = 0; i < 5; ) {
		comNumber = rand() % 3;

		cout << i << "번째 게임" << endl;
		// 치트
		cout << "컴퓨터가 고른 숫자는 " << comNumber << "입니다" << endl;
		cout << "0.가위 , 1.바위 , 2.보 중에서 선택하세요" << endl;
		cin >> selectNumber;
		if (0 > selectNumber || selectNumber > 2) {
			cout << "다시 선택하세요" << endl;
			continue;
		}

		switch (selectNumber)
		{
		case 0:		// 플레이어 가위
			switch (comNumber) 
			{
			case 0: // 컴퓨터 가위
				cout << "비겼다" << endl;
				break;
			case 1: // 컴퓨터 바위
				cout << "컴퓨터가 바위로 이겼다" << endl;
				loseCount++;
				break;
			case 2: // 컴퓨터 보
				cout << "플레이어가 가위로 이겼다" << endl;
				winCount++;
				break;
			}
			break;
		case 1:		// 플레이어 바위
			switch (comNumber)
			{
			case 0: // 컴퓨터 가위
				cout << "플레이어가 바위로 이겼다" << endl;
				winCount++;
				break;
			case 1: // 컴퓨터 바위
				cout << "비겼다" << endl;
				break;
			case 2: // 컴퓨터 보
				cout << "컴퓨터가 보로 이겼다" << endl;
				loseCount++;
				break;
			}
			break;
		case 2:		// 플레이어 보
			switch (comNumber)
			{
			case 0: // 컴퓨터 가위
				cout << "컴퓨터가 가위로 이겼다" << endl;
				loseCount++;
				break;
			case 1: // 컴퓨터 바위
				cout << "플레이어가 보로 이겼다" << endl;
				winCount++;
				break;
			case 2: // 컴퓨터 보
				cout << "비겼다" << endl;
				break;
			}
			break;
		}
		i++;
	}
	
	cout << "플레이어 : " << winCount << " 승리, " 
		<< loseCount << " 패배, " 
		<< 5 - winCount - loseCount << " 무승부" << endl;

	cout << "최종결과 : ";
	if (winCount > loseCount) {
		cout << "플레이어의 승리" << endl;
	}
	else if (winCount < loseCount) { 
		cout << "컴퓨터의 승리" << endl;
	}
	else // (winCount == loseCount) 
	{
		cout << "비겼다" << endl;
	}
}