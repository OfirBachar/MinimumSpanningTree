#pragma once
#include "definitions.h"

class PriorityQueue
{
private:
	vector<Pair*> m_PriorityQueueData;
	vector<int> m_indexsInPQ;
	int m_Size;

	static int Left(int i_VertexIndex);
	static int Right(int i_VertexIndex);
	static int Parent(int i_VertexIndex);
	void FixHeap(int i_VertexIndex);
	void fixHeapBubble(int i_Index);

public:
	PriorityQueue(int i_NumOfVertices);
	void Build(vector<Pair*> i_NewPriorityQueueArr);
	Pair* DeleteMin();
	bool IsEmpty();
	void DecreaseKey(int i_Place, int i_NewKey);
	~PriorityQueue();

	friend class Graph;
};

