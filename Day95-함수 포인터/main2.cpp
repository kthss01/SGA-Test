#include <Windows.h>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

class Game {
public:
	static void Start(int number) {
		printf("%d번째 게임의 시작 \n", number);
	}

	void Render(int number) {
		printf("%d번째 렌더링\n", number);
	}
};

class Launch {
public:
	Launch() {
		// static이어서 바로 넣을 수 있음
		start = Game::Start;
		// Game이 가지고 있는 녀석을 넣어야하는데 static이라 하나만 존재해서 안됨
		//render = Game::Start; 
		// Game::Render 단독으로 쓸 수 없기 때문에 Game이 가지고 있는 Render가 필요해서 주소값으로 받아씀
		render = &Game::Render;
	}
	void Execute(int number) {
		start(number);
		Game ob;
		(ob.*render)(number);
	}
private:
	void(*start)(int) = NULL;
	void(Game::*render)(int) = NULL;
};

int main() {
	Launch * ob = new Launch();
	ob->Execute(10);
	
	return 0;
}