#include "pch.h"
#include "PriorityQueue.h"

void InitPQ(PQ* pq)
{
	pq->heap_size = 0;
}

void PQNodeOperator_Insert(PQNode* node, PQNode* other)
{
	node->f = other->f;
	node->g = other->g;
	node->pos = other->pos;
}

void PushPQLower(PQ* pq, PQNode data)
{
	pq->heap_size = pq->heap_size + 1;
	int i = pq->heap_size;
	while ((i != 1) && (data.f > pq->heap[i / 2].f))
	{
		//q->heap[i] = q->heap[i / 2];
		PQNodeOperator_Insert(&pq->heap[i], &pq->heap[i / 2]);
		i /= 2;
	}
	//q->heap[i] = data;
	PQNodeOperator_Insert(&pq->heap[i], &data);
}

PQNode PopPQLower(PQ* q)
{
	int parent = 1, child = 2;
	PQNode data, temp;
	data = q->heap[1];
	temp = q->heap[q->heap_size];
	q->heap_size = q->heap_size - 1;

	while (child <= q->heap_size)
	{
		if ((child < q->heap_size) && (q->heap[child].f) < q->heap[child + 1].f)
			child++;
		if (temp.f >= q->heap[child].f) break;
		//q->heap[parent] = q->heap[child];
		PQNodeOperator_Insert(&q->heap[parent], &q->heap[child]);
		parent = child;
		child = child * 2;
	}
	//q->heap[parent] = temp;
	PQNodeOperator_Insert(&q->heap[parent], &temp);

	return data;
}



void PushPQUpper(PQ* pq, PQNode data)
{
	pq->heap_size = pq->heap_size + 1;
	int i = pq->heap_size;
	while ((i != 1) && (data.f < pq->heap[i / 2].f))
	{
		//q->heap[i] = q->heap[i / 2];
		PQNodeOperator_Insert(&pq->heap[i], &pq->heap[i / 2]);
		i /= 2;
	}
	//q->heap[i] = data;
	PQNodeOperator_Insert(&pq->heap[i], &data);

}
PQNode PopPQUpper(PQ* q)
{
	int parent = 1, child = 2;
	PQNode data, temp;
	data = q->heap[1];
	temp = q->heap[q->heap_size];
	q->heap_size = q->heap_size - 1;

	while (child <= q->heap_size)
	{
		if ((child < q->heap_size) && (q->heap[child].f) > q->heap[child + 1].f)
			child++;
		if (temp.f <= q->heap[child].f) break;
		//q->heap[parent] = q->heap[child];
		PQNodeOperator_Insert(&q->heap[parent], &q->heap[child]);
		parent = child;
		child = child * 2;
	}
	//q->heap[parent] = temp;
	PQNodeOperator_Insert(&q->heap[parent], &temp);

	return data;
}

int CheckEmptyPQ(PQ* pq)
{
	if (pq->heap_size != 0) return 0;
	else return 1;
}

PQNode TopPQ(PQ* pq)
{
	return pq->heap[1];
}
