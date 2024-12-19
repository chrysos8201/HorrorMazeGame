#include "pch.h"

const int dy[] = { -1, 0, 1, 0, -1, 1, 1, -1 };
const int dx[] = { 0, 1, 0, -1, 1, 1, -1, -1 };
const int cost[] = { 10, 10, 10, 10, 14, 14, 14, 14 };

HashMap* Astar(Pos startPos, Pos destPos)
{
	HashMap* parent = createHashMap(HASH_KEY);
	for (int i = 0; i < HEIGHT; i++)
		for (int j = 0; j < WIDTH; j++)
			best[i][j] = INT32_MAX;

	PQ pq;
	InitPQ(&pq);

	// 초기 값 지정 블록
	{
		
		int g = 0;
		int h = 10 * (abs(destPos.y - startPos.y) + abs(destPos.x - startPos.x));
		PQNode node = { g + h, g, {startPos.y, startPos.x} };
		PushPQUpper(&pq, node);
		best[startPos.y][startPos.x] = g + h;

		// 부모 찾기
		put(parent, startPos, startPos);
	}
	while (!CheckEmptyPQ(&pq))
	{
		PQNode node;
		node.f = TopPQ(&pq).f;
		node.g = TopPQ(&pq).g;

		Pos p;	
		p.y = TopPQ(&pq).pos.y;
		p.x = TopPQ(&pq).pos.x;

		PopPQUpper(&pq);	// pop 여기서 할 것!
		node.pos = p;
		
		// 이미 더 좋은 경로가 있다면 스킵
		if (best[node.pos.y][node.pos.x] < node.f)
			continue;

		// 도착 지점에 도달하였을 경우 break
		if (PosOperator_IsSame(node.pos, destPos)) {
			break;
		}

		for (int dir = 0; dir < 8; dir++)
		{
			Pos nextPos;
			nextPos.y = node.pos.y + dy[dir];
			nextPos.x = node.pos.x + dx[dir];


			// 맵 바깥으로 벗어나면 스킵
			if (nextPos.y < 0 || nextPos.y > HEIGHT - 1 || nextPos.x < 0 || nextPos.x > WIDTH - 1)
				continue;

			// 벽 체크
			if (map[nextPos.y][nextPos.x])
				continue;


			// 비용 계산
			int g = node.g + cost[dir];
			int h = 10 * (abs(destPos.y - nextPos.y) + abs(destPos.x - nextPos.x));

			// 이미 더 좋은 경로가 있다면 스킵
			if (best[nextPos.y][nextPos.x] <= g + h)
				continue;
			best[nextPos.y][nextPos.x] = g + h;

			PQNode nextPqNode = { g + h, g, nextPos };
			PushPQUpper(&pq, nextPqNode);

			// 최종 path를 위한 key와 value 저장
			put(parent,nextPos, node.pos);
		}
	}
	return parent;
}