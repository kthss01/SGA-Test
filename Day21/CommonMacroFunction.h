#pragma once

//////////////////////////////////////////////////////////////////
// CommonMacroFunction (�ʿ��� �κ��� ���� ���� �߰� �Ұ�)
//////////////////////////////////////////////////////////////////

// POINT -> (LONG x, LONG y) �Ǿ� �ִ� ����ü

// inline �ߺ����� ���ϴ°�

inline POINT PointMake(int x, int y) {
	POINT pt = { x, y };
	return pt;
}

inline void LineMake(HDC hdc, int x1, int y1, int x2, int y2) {
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

inline RECT RectMake(int x, int y, int width, int height) {
	RECT rc = { x, y, x + width, y + height };
	return rc;
}

inline void RectangleMake(HDC hdc, int x, int y, int width, int height) {
	Rectangle(hdc, x, y, x + width, y + height);
}