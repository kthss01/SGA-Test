#pragma once
#include "MainGame3.h"

// 템플릿 : 여러가지 함수 및 클래스를 찍어내는 틀이라고 생각

// 클래스에다 템플릿하면 클래스 포함한거 다 템플릿
class Template
{
public:
	Template();
	~Template();

	// 이렇게도 가능하지만 템플릿으로 가능
	//void Output(int data);
	//void Output(float data);
	//void Output(char* data);

	template<typename T>	// 바로 아래만 가능
	void Output(T data);
};

// 헤더에 선언하면 cpp에 작업할 수 없음
// 함수 호출하는데도 순번 있음
// inline 붙이면 앞으로 순번 땡긴다고 보면 됨
template<typename T>
inline void Template::Output(T data)
{
	cout << "데이터 : " << data << endl;
}
