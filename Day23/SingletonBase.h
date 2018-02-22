#pragma once

// SingletonBase.h

// 싱글턴 패턴 - 디자인 패턴 중 하나
// 쓰는 이유 : 객체를 하나만 만드는 이유가 있어서 ( new를 한번만 한다 )
// 저장해서 사용할 때 singleton 붙여서 사용하는 경우가 많음 이미지 같은거

// 템플릿 이용해서 만드면 템플릿 싱글톤
// 그냥 만들면 다이나믹 싱글톤 이렇게 되는데 하는 역할은 똑같음 -> 객체 하나 만듬

template <typename T>
class SingletonBase
{
protected:
	// 싱글톤 인스턴스
	static T* instance;
	SingletonBase() {};
	~SingletonBase() {};

public:
	// 싱글톤 객체 가져오기
	static T* GetSingleton();
	void ReleaseSingleton();
};

// 싱글톤 인스턴스 선언
template<typename T>
T* SingletonBase<T>::instance = NULL;

template<typename T>
T * SingletonBase<T>::GetSingleton()
{
	// 싱글톤 객체가 없으면 새로 생성
	if (!instance) instance = new T;
	// 존재하면 반환
	return instance;
}

// 싱글톤 메모리 해제는 게임이 종료될때 하게 되므로 너무 많은건 않좋음
template<typename T>
void SingletonBase<T>::ReleaseSingleton()
{
	if (instance) {
		delete instance;
		instance = 0;
	}
}

// 일반적 다이나믹 싱글톤은
// 생성자 소멸자 private protected 로 묶어서 하게됨 
// 외부에서 참조(new 할당) 못하게 하게