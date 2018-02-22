#include <iostream>
#include <time.h>
#include <Windows.h>
using namespace std;

// Up - Down Game
void main() {
	srand(time(NULL));

	int randomNumber;
	int selectNumber;

	randomNumber = rand() % 100 + 1;
	// 0 ~ 99 + 1 -> 1 ~ 100
	int GameCount = 0;
	while (GameCount < 10)
	{
		cout << GameCount + 1 << "번째 입력" << endl;
		cout << "1 ~ 100 사이의 숫자를 입력 : ";
		cin >> selectNumber;

		Sleep(1000);	// 1000 (1초)간 화면만 잠깐 멈춤
						// sleep 동안 입력값은 화면에 보이지 않을 뿐 들어가 있음
		system("cls");	// 화면 지워줌

		if (randomNumber > selectNumber) {
			cout << "Up" << endl;
		}
		else if (randomNumber < selectNumber) {
			cout << "Down" << endl;
		}
		else {
			cout << "Find " << randomNumber << endl;
			break;
		}

		GameCount++;
	}

	// 콘솔창에서 cls 명령 치면 화면 지워줌
	// system() 콘솔명령어 실행하는 것

	/// window.h 라이브러리 좀 알아두면 좋을듯 
	/// 하나씩 설명하는게 보니까 이걸로 뭐 하는듯
}