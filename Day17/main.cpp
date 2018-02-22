#include "DrawImage.h"

// �� �̹����� ���Ĺ����� �浹 üũ�Ѵٰ� �����ϸ� ��
bool Collision(Rect rect1, Rect rect2) {
	// rect1.x ������ ������ , rect1.x+rec1.width �������� ������

	int left = rect2.X;
	int top = rect2.Y;
	int right = rect2.X + rect2.Width;
	int bottom = rect2.Y + rect2.Height;

	// (left or right) and (top or bottom) -> �浹 �ߴ�.
	// ���� ���� left�� rect1�� �� ������ ���̿� �ִ��� �ǹ�

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

	//// ����ȯ ���� ����� L���� WCHAR* �� �������
	//npc->AddImage((WCHAR*)L"Npc.png"); // ���� �����ڵ� ���� �����ε� 
	//// WCHAR �� �־��ַ��� �տ� L�� �ٿ������

	//Sleep(1000);
	//// ������ ���� ��� 0,0 *����Ƽ�� ���� �ϴ� ����
	//npc->Drawing(100, 100);
	//// ȭ���� ġ��� ����� �����Ͱ� ���� ����

	//getch();
	//npc->Clear(128, 128, 128);	// ȸ�� 128 128 128

	// x,y, width, height
	// ��ǥ���� �ȼ���
	Gdiplus::Rect rect = { 200, 400, 150, 150 };	
	//Gdiplus::Rect rect = { 200, 400, 200, -300 };	// ������ ���
	Rect rect2 = { 500, 400, 100, 150 };

	//bool isLeft = false;
	STATE state = STATE_RIGHT;

	// ȸ���ϴ°͵� ���� (������ �ϴٰ� �˰� ���� �����)
	// ������ : �ȼ��� ���� ������ �˰� �־����
	// ������ ���� �̹����� �þ�� ������ ����

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

		char key = _getch();	// 15���� ���� ���� getch(), 
		// �̰� 17���� _getch 
		// 17������ ū ���� x, ������ ȣȯ�� �̷��� ���׷��̵�̴ٰ� �����
		// 15������ �ַ� �� 17�� ���� �ƿ� �Ⱦ��ٰ� ���� �� (���������� �ʾƼ�)
		// ¦�������� ������ ���� ���� directX �� 9������ ���̾� 10�� ����, 11 ��
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
	Rect �簢�� ����
	Api ���� ���� ���� �Ẽ��
*/

/*
	����

	�̹����� �׸��� Ű���� �Է����� �̵���Ű��
	w,a,s,d �� �����̰Բ�

*/

/*
	����2 18.02.16(ȭ) 18����

	�̹��� 2��
			a			b
						ab 

			a�����̴� b������ ���� �����̰� 
			ab �϶� ������ ������ (�浹)
*/

/*
	�ִϸ��̼� ���
	���� ������ ����
	��������Ʈ �̹��� : �����̴� �̹��� ������
	// ���� �ڵ�� �ڸ��°�
	2d spine 2d�� 3d����ó�� ����°� 3d �� �����̴°� ���ְ� ������
	��������ۿ� ����
*/

/*
	������ �浹üũ ���
	�浹�� �簢���� ���������� ������ Ȯ��

*/