#pragma once
#include "Unit.h"
#include "Enemy.h"

// 상속
/*
	공통된 특성을 묶어서 자식에게 그 특성을 물려 주는 것
	ex) 동물 -> 원숭이, 호랑이, 토끼 등등

	공통의 기능을 상위 클래스에 묶어 넣어 
	다른 클래스로 확장이 용이 하게 진행하기 위해서
	코드 수정하기 쉬워서
*/

/// 게임잡 많이 뽑음

// protected, private 상속은 잘 안씀

// override 하지 않으면 함수의 주소값이 다름
// 그래서 캐스팅 했을 때 호출이 달라짐

class Monster : public Unit, protected Enemy	// 다중 상속 (잘 안씀, 피하면 좋음)
	/// 프레임워크 작업하기 시작하면 클래스가 많이 다루게 될 때 다중 상속 쓰게되면 코드가 꼬이기 쉬움
{
public:
	Monster();
	~Monster();

	void Move();	// 이름은 동일하지만 다른 함수	Unit::Move()와는 다른 함수
	void Attack() override;	// override 안 붙여도 됨, virtual 앞에 붙여도 다 재정의임
	/// override 붙여두면 오타시 에러뜸 재정의 했는지 확인 해줌

	virtual void AttackPlayer() override; 
	// 가능하면 override 붙여주는게 좋음 
	// (보통 오타 검사 위해서), virtual 가독성을 위해서 붙이는거
};

