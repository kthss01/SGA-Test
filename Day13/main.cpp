#include "Monster.h"

// �����Լ� ��� ���迡�� ����ϸ�
// �θ𿡰� ��� ���� �Լ��� ������ �����
// ������ �ٽ� �ۼ��ؼ� �Լ��� ����Ѵ� (overriding)

// �Լ��� �̸��� ���������� ���ڰ��� �ٸ� �༮ (overloading)

// java ��� ��ũ�����̸����� ����

void Action(Unit* unit) {
	unit->Attack();
	unit->Move();
}

/// ���� ���� �� ���� �� �ִ°� �׶� (3D)
/// 2D�� ��������

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
	//ms3 = new Unit;			// �ڽĿ� �θ� �ּҰ����� ���� �� ���� �Ұ�
	//ms1 = new Monster;		// �̰� ����

	/*Action(ms1);
	Action(ms2);*/

	ms1->Move();
	ms2->Move();

	ms1->Attack();
	ms2->Attack();
}