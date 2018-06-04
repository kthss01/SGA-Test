#include "stdafx.h"
#include "CircularQueue.h"


CircularQueue::CircularQueue()
	:nFront(0), nRear(0)
{
}


CircularQueue::~CircularQueue()
{
}

void CircularQueue::Enqueue(int n)
{
	if (IsFull()) return;

	aData[nRear] = n;
	nRear = (nRear + 1) % QUEUE_SIZE;
}

void CircularQueue::Dequeue()
{
	if (IsEmpty()) return;

	nFront = (nFront + 1) % QUEUE_SIZE;
}

void CircularQueue::Print()
{
	for (int i = nFront; i != nRear; i = (i+1) % QUEUE_SIZE) {
		std::cout << aData[i] << std::endl;
	}
}

int CircularQueue::Percent()
{
	int cnt = 0;
	for (int i = nFront; i != nRear; i = (i + 1) % QUEUE_SIZE) {
		cnt++;
	}
	return (float)cnt / (float) QUEUE_SIZE * 100.0f;
}

bool CircularQueue::IsFull()
{
	return (nRear + 1) % QUEUE_SIZE == nFront;
}

bool CircularQueue::IsEmpty()
{
	return nFront == nRear;
}
