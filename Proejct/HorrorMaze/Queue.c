#include "pch.h"
#include "Queue.h"


void InitQueue(Queue* q)
{
	q->front = q->rear = q->queue_size = 0;
}
void ClearQueue(Queue* q)
{
	q->front = q->rear;
	q->queue_size = 0;
}
void PushQueue(Queue* q, Pos pos)
{
	if ((q->rear + 1) % MAX_QUEUE_ELEMENT == q->front) {    // Å¥°¡ ²Ë Ã¡´ÂÁö È®ÀÎ
		return;
	}
	q->queue[q->rear] = pos;
	q->rear = ++(q->rear) % MAX_QUEUE_ELEMENT;

	q->queue_size++;
	return;
}
const Pos FrontQueue(Queue* q)
{
	if (q->front == q->rear) {
		Pos p; p.x = 0, p.y = 0;
		return p;
	}
	Pos ret = q->queue[q->front];
	return ret;
}
Pos PopQueue(Queue* q)
{
	if (q->front == q->rear) {
		Pos p; p.x = 0, p.y = 0;
		return p;
	}
	Pos ret = q->queue[q->front];
	q->front = ++(q->front) % MAX_QUEUE_ELEMENT;

	q->queue_size--;
	return ret;
}

void QueueOperator_Insert(Queue* q, Queue* other)
{
	q->front = other->front;
	q->rear = other->rear;
	q->queue_size = other->queue_size;
	for (int i = other->front % MAX_QUEUE_ELEMENT; i != other->rear; i++)
	{
		q->queue[i] = other->queue[i];
	}
}