#include "stdafx.h"
#include "Util.h"

namespace MY_UTIL
{
	float GetAngle(float startX, float startY, float endX, float endY) {
		float x = endX - startX;
		float y = endY - startY;

		float distance = sqrtf(x * x + y * y);
		float angle = acosf(x / distance);

		if (endY > startY) {
			angle = -angle;
			if (angle >= PI * 2) angle -= PI * 2;
		}
		return angle;
	}
	float GetDistance(float startX, float startY, float endX, float endY) {
		float x = endX - startX;
		float y = endY - startY;

		float distance = sqrtf(x * x + y * y);
		return distance;
	}
	bool IntersectLine(POINT FLineP1, POINT FLineP2, POINT SLineP1, POINT SLineP2)
	{
		// ���� ������ �浹�ϴ� ��� ���� ����
		// ������ �ƴ� �������� ����ϴ°� 
		// ������ ������ ���ݴ� ����ϱ� ����
		// �� ������ ã�°�

		/*
			�� (x1, y1), (x2, y2) �������� ��Ÿ���� ��
			�� (x3, y3), (x4, y4) ������ ��Ÿ���� ��
			4���� ������ ���� ��

			den = (y4 - y3) x (x2 - x1) - (x4 - x3) x (y2 - y1)
			den == 0 ����
			
			ua = ((x4 - x3) x (y1 - y3) - (y4 - y3) x (x1 - x3)) / den
			ub = ((x2 - x1) x (y1 - y3) - (y2 - y1) x (x1 - x3)) / den

			0 < ua, ub < 1 �϶� �浹

		*/

		float x;
		float y;
		float den = ((FLineP2.x - FLineP1.x) * (SLineP2.y - SLineP1.y) -
			(SLineP2.x - SLineP1.x) * (FLineP2.y - FLineP1.y));

		if (den == 0) return false;

		x = (SLineP2.x - SLineP1.x) * (FLineP1.y - SLineP1.y) -
			(SLineP2.y - SLineP1.y) * (FLineP1.x - SLineP1.x) / den;
			
		y = ((FLineP2.x - FLineP1.x) * (FLineP1.y - SLineP1.y) -
			(FLineP2.y - FLineP1.y) * (FLineP1.x - SLineP1.x)) / den;

		bool check = false;
		if ((0 < x && x < 1) && (0 < y && y < 1)) {
			check = true;
		}

		return check;
	}
	void tagRay::DrawRay(HDC hdc)
	{
#ifdef _DEBUG
		LineMake(hdc, origin, direction);
#endif // _DEBUG
	}
	bool tagRay::CollisionRect(RECT rc)
	{
		//// ���� �簢�� �浹
		//// ���� ����� ������ ������ ����غ� ��
		//
		//POINT point[4];
		//
		//point[0] = { rc.left, rc.top };
		//point[1] = { rc.right, rc.top };
		//point[2] = { rc.left, rc.bottom };
		//point[3] = { rc.right, rc.bottom };
		//
		//int startX = origin.x;
		//int endX = direction.x;
		//
		//if (startX > endX) {
		//	int temp = startX;
		//	startX = endX;
		//	endX = temp;
		//}
		//
		//int startY = origin.y;
		//int endY = direction.y;
		//
		//if (startY > endY) {
		//	int temp = startY;
		//	startY = endY;
		//	endY = temp;
		//}
		//
		//for (int i = 0; i < 4; i++) {
		//	bool checkX = false;
		//	bool checkY = false;
		//	if (startX < point[i].x && point[i].x < endX) checkX = true;
		//	if (startY < point[i].y && point[i].y < endY) checkY = true;
		//
		//	if (checkX && checkY) return true;
		//}
		//
		//return false;	
		
		// ���� �簢�� �浹
		// ���浹�� �ٲ�

		// �簢��
		POINT point[5];

		point[0] = { rc.left, rc.top };
		point[1] = { rc.right, rc.top };
		point[2] = { rc.right, rc.bottom };
		point[3] = { rc.left, rc.bottom };
		point[4] = { rc.left, rc.top };

		bool check = false;
		for (int i = 0; i < 4; i++) {
			bool check2 = 
				IntersectLine(origin, direction, point[i], point[i + 1]);
			check |= check2;
		}

		return check;
	}
}