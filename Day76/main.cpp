#include "SLL.h"

void main() {
	SLL sll;

	for (int i = 0; i < 10; i++)
		sll.Add(i);
	sll.Print();

	sll.Insert(4, 100);
	sll.Print();

	sll.Delete(100);
	sll.Print();

	sll.Reverse();
	sll.Print();
}