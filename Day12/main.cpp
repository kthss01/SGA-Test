// main.cpp

#include "MainGame2.h"

void main() {
	MainGame2 mg;

	mg.Init();
	while (true) {
		mg.Update();
		if (mg.GetIsBetting() == false) {
			break;
		}
	}
}

// 과제
// 한줄 조사
// STL vector, STL map

// 내일이나 모래 나올 과제 (주말 전에)

/*
	상점에서 방어구 무기 악세 포션 살 수 있음
	판매도 가능 (절반값으로 판매)
	돈 부족하면 못삼
	구매하여 장착도 가능하고 스텟에 변화도 주는
	장착되면 인벤토리에서 사라지고 상태창에서 장착 보여줌

	// 실행 파일 올려줄 꺼
*/