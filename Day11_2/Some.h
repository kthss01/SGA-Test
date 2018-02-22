#pragma once
#include <iostream>
using namespace std;

class Some
{
private:
	int posX;
	int posY;
public:
	Some();
	~Some();
	
	// 외부에서 private에 있는 변수 수정하기 위해서

	// Getter GetFunction
	int GetPosX() { return posX; }
	int GetPosY() { return posY; }
	// Setter SetFunction
	void SetPosX(int x) { posX = x; }
	void SetPosY(int y) { posY = y; }

	void Render() { cout << posX << " " << posY << endl; }
};

