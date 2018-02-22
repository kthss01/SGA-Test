#include "Monster.h"

// 가상함수 상속 관계에서 사용하며
// 부모에게 상속 받은 함수의 내용을 지우고
// 내용을 다시 작성해서 함수를 사용한다 (overriding)

// 함수의 이름은 동일하지만 인자값이 다른 녀석 (overloading)

// java 어원 오크나무이름에서 따옴

void Action(Unit* unit) {
	unit->Attack();
	unit->Move();
}

/// 가장 쉽게 모델 뜯을 수 있는게 테라 (3D)
/// 2D도 마찬가지

void main()
{
	//Monster ms;
	//ms.Attack();
	//ms.Move();

	//// upcasting
	//Monster* m = new Monster;
	//Unit* u = dynamic_cast<Monster*>(m);
	//u->Attack();

	Unit* ms1;
	Monster* ms2;
	Monster* ms3;

	ms1 = new Monster;
	ms2 = new Monster;
	//ms3 = new Unit;			// 자식에 부모를 주소값으로 담을 수 없음 불가
	//ms1 = new Monster;		// 이건 가능

	/*Action(ms1);
	Action(ms2);*/

	ms1->Move();
	ms2->Move();

	ms1->Attack();
	ms2->Attack();
}