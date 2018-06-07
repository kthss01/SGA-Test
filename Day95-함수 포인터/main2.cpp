#include <Windows.h>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

class Game {
public:
	static void Start(int number) {
		printf("%d��° ������ ���� \n", number);
	}

	void Render(int number) {
		printf("%d��° ������\n", number);
	}
};

class Launch {
public:
	Launch() {
		// static�̾ �ٷ� ���� �� ����
		start = Game::Start;
		// Game�� ������ �ִ� �༮�� �־���ϴµ� static�̶� �ϳ��� �����ؼ� �ȵ�
		//render = Game::Start; 
		// Game::Render �ܵ����� �� �� ���� ������ Game�� ������ �ִ� Render�� �ʿ��ؼ� �ּҰ����� �޾ƾ�
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