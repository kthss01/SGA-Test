#include "SLL.h"

void main() {
	SLL sll;

	for (int i = 0; i < 10; i++)
		sll.Add(i);

	sll.Print();
}