#pragma once

#define QUEUE_SIZE 5

class CircularQueue
{
private:
	int aData[QUEUE_SIZE];
	int nFront;
	int nRear;
public:
	CircularQueue();
	~CircularQueue();

	void Enqueue(int n);
	void Dequeue();
	void Print();
	int Percent();
	bool IsFull();
	bool IsEmpty();
};

