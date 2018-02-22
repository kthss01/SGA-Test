#pragma once
/*
	객체 지향 코딩	- 유지보수가 쉬워서가 주된 이유
	객체 -> 데이터, 행동, identity(특성) 
	.h(헤더), .cpp

	-> .h (선언) int num; void Add();	// 보기 쉽도록 헤더엔 선언만 쓰게됨

*/
/*
	접근 지정자
	public, protected, private

	public -> 모든 클래스에서 사용할 수 있는
	protected -> 상속 (부모 자식 관계)을 받은 클래스까지만 사용 가능
	private -> 자기 자신만 사용할 수 있는
*/

/*
	생성자 -> 클래스가 처음 생성됐을 때 1번 실행
	소멸자 -> 클래스가 처음 소멸됐을 때	1번 실행
*/

class MainGame
{
private:
	int m_x, m_y;	// 클래스 내 맴버 변수 선언

public:
	MainGame();		// 생성자
	~MainGame();	// 소멸자

	// 드래그 후 전구 클릭하면 자동으로 cpp에서 정의 만들어 줌
	void PublicFunction();

protected:
	void ProtectedFunction();

private:
	void PrivateFunction();
};

