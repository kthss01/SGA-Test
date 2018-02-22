#include "DrawImage.h"

// 두 이미지가 겹쳐버리면 충돌 체크한다고 생각하면 됨
bool Collision(Rect rect1, Rect rect2) {
	// rect1.x 왼쪽위 꼭지점 , rect1.x+rec1.width 오른쪽위 꼭지점

	int left = rect2.X;
	int top = rect2.Y;
	int right = rect2.X + rect2.Width;
	int bottom = rect2.Y + rect2.Height;

	// (left or right) and (top or bottom) -> 충돌 했다.
	// 참인 경우는 left가 rect1의 두 꼭지점 사이에 있는지 의미

	if ((rect1.X <= left && left <= rect1.X + rect1.Width)
		|| (rect1.X <= right && right <= rect1.X + rect1.Width)) {
		if ((rect1.Y <= top && top <= rect1.Y + rect1.Height)
			|| (rect1.Y <= bottom && bottom <= rect1.Y + rect1.Height)) {
			return true;
		}
	}
	return false;
}

enum STATE {
	STATE_RIGHT, STATE_LEFT, STATE_BOTTOM, STATE_TOP
};

void main() {
	DrawImage* npc = new DrawImage();
	DrawImage* image = new DrawImage();

	//// 형변환 문제 생기면 L옆에 WCHAR* 로 해줘야함
	//npc->AddImage((WCHAR*)L"Npc.png"); // 현재 유니코드 문자 집합인데 
	//// WCHAR 에 넣어주려면 앞에 L을 붙여줘야함

	//Sleep(1000);
	//// 기준점 왼쪽 상단 0,0 *유니티는 왼쪽 하단 기준
	//npc->Drawing(100, 100);
	//// 화면을 치우면 사라짐 데이터가 남지 않음

	//getch();
	//npc->Clear(128, 128, 128);	// 회색 128 128 128

	// x,y, width, height
	// 좌표값은 픽셀임
	Gdiplus::Rect rect = { 200, 400, 150, 150 };	
	//Gdiplus::Rect rect = { 200, 400, 200, -300 };	// 뒤집는 방법
	Rect rect2 = { 500, 400, 100, 150 };

	//bool isLeft = false;
	STATE state = STATE_RIGHT;

	// 회전하는것도 가능 (가능은 하다고 알고 있음 어려움)
	// 문제점 : 픽셀에 대한 정보를 알고 있어야함
	// 각도에 따라 이미지가 늘어나는 경향이 있음

	//npc->AddImage(L"NPC2.png", rect);
	//npc->AddImage(L"NPC.png", rect);

	// 0 ~ 1 right 2 ~ 3 left
	npc->AddImage(L"Images/right1.png", rect);
	npc->AddImage(L"Images/right2.png", rect);

	npc->AddImage(L"Images/left1.png", rect);
	npc->AddImage(L"Images/left2.png", rect);

	npc->AddImage(L"Images/front1.png", rect);
	npc->AddImage(L"Images/front2.png", rect);
	
	npc->AddImage(L"Images/back1.png", rect);
	npc->AddImage(L"Images/back2.png", rect);

	image->AddImage(L"Npc.png", rect2);

	//npc->Drawing(0);

	//npc->Drawing(200, 200);

	//getch();

	//int posX = 0;
	//int posY = 0;
	
	//int count = 0;
	//int index = 0;

	//while (true) {
	//	Sleep(100);
	//	count++;

	//	if (count % 10 == 0)
	//		index++;

	//	npc->Clear(0, 0, 0);
	//	//posX += 10;
	//	//npc->Drawing(posX, posY);
	//	rect.X += 5;
	//	//npc->Drawing(posX, posY);
	//	npc->Drawing(index % 2, rect);
	//}
	
	int count = 0;
	int index = 0;
	while (true) {
		npc->Clear(0, 0, 0);
		Sleep(10);
		// 0,1 R  2,3 L
		//if (isLeft == true) {
		//	npc->Drawing(index % 2 + 2, rect);
		//}
		//else {
		//	npc->Drawing(index % 2, rect);
		//}

		npc->Drawing(index % 2 + 2 * state, rect);

		image->Drawing(0, rect2);

		char key = _getch();	// 15버전 이전 버전 getch(), 
		// 이건 17이후 _getch 
		// 17버전은 큰 차이 x, 안전성 호환성 이런거 업그레이드됫다고 보면됨
		// 15버전을 주로 씀 17은 아직 아예 안쓴다고 보면 됨 (안정적이지 않아서)
		// 짝수버전은 문제가 많은 편임 directX 도 9버전은 많이씀 10은 망함, 11 씀
		switch (key) {
		case 'a':
			//isLeft = true;
			state = STATE_LEFT;
			rect.X -= 5;
			count++;
			break;
		case 'd':
			//isLeft = false;
			state = STATE_RIGHT;
			rect.X += 5;
			count++;
			break;
		case 'w':
			state = STATE_TOP;
			rect.Y -= 5;
			count++;
			break;
		case 's':
			state = STATE_BOTTOM;
			rect.Y += 5;
			count++;
			break;
		}

		if (Collision(rect, rect2)) {
			//if (isLeft == true) {
			//	rect2.X -= 5;
			//}
			//else
			//	rect2.X += 5;
			switch (state)
			{
			case STATE_RIGHT:
				rect2.X += 5;
				break;
			case STATE_LEFT:
				rect2.X -= 5;
				break;
			case STATE_BOTTOM:
				rect2.Y += 5;
				break;
			case STATE_TOP:
				rect2.Y -= 5;
				break;
			default:
				break;
			}
		}

		if (count % 10 == 1) {
			index++;
		}
	}

	delete npc;
	delete image;
}

/*
	Rect 사각형 뜻함
	Api 들어가기 전에 많이 써볼꺼
*/

/*
	과제

	이미지를 그리고 키보드 입력으로 이동시키기
	w,a,s,d 로 움직이게끔

*/

/*
	과제2 18.02.16(화) 18일차

	이미지 2장
			a			b
						ab 

			a움직이다 b만나면 같이 움직이게 
			ab 일때 떨어져 나가게 (충돌)
*/

/*
	애니메이션 방식
	사진 여러개 연속
	스프라이트 이미지 : 움직이는 이미지 모은거
	// 그중 코드로 자르는거
	2d spine 2d를 3d형식처럼 만드는거 3d 모델 움직이는거 본넣고 움직임
	유료버전밖에 없음
*/

/*
	간단한 충돌체크 방식
	충돌할 사각형에 꼭지점들이 들어가는지 확인

*/