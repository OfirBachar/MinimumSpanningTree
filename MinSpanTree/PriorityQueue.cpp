#include "PriorityQueue.h"

int PriorityQueue::Left(int i_VertexIndex)
{
	return (2 * i_VertexIndex + 1);
}

int PriorityQueue::Right(int i_VertexIndex)
{
	return (2 * i_VertexIndex + 2);
}

int PriorityQueue::Parent(int i_VertexIndex)
{
	return (i_VertexIndex - 1) / 2;
}

PriorityQueue::PriorityQueue(int i_NumOfVertices)
{
	for (int i = 0; i < i_NumOfVertices; i++)
	{
		m_indexsInPQ.push_back(i);
	}

	m_Size = i_NumOfVertices;
}

void PriorityQueue::Build(vector<Pair*> i_NewPriorityQueueArr)
{
	for (int i = 0; i < i_NewPriorityQueueArr.size(); i++)
	{
		Pair* pair = new Pair;
		pair->vertexIndex = i_NewPriorityQueueArr[i]->vertexIndex;
		pair->weight = i_NewPriorityQueueArr[i]->weight;
		m_PriorityQueueData.push_back(pair);
	}

	for (int i = (m_PriorityQueueData.size() / 2) - 1; i >= 0; i--)
	{
		FixHeap(i);
	}
}

Pair* PriorityQueue::DeleteMin()
{
	if (m_Size < 1)
	{
		cout << "error";
		exit(1);
	}

	Pair* min = m_PriorityQueueData[0];
	m_Size--;
	m_PriorityQueueData[0] = m_PriorityQueueData[m_Size];
	m_indexsInPQ[m_PriorityQueueData[m_Size]->vertexIndex - 1] = 0;
	m_PriorityQueueData.resize(m_Size);
	FixHeap(0);

	return min;
}

bool PriorityQueue::IsEmpty()
{
	return m_Size == 0;
}

void PriorityQueue::DecreaseKey(int i_Index, int i_NewWeight)
{
	m_PriorityQueueData[i_Index]->weight = i_NewWeight;
	fixHeapBubble(i_Index);
}

void PriorityQueue::FixHeap(int i_Index)
{
	int min;
	int left = Left(i_Index);
	int right = Right(i_Index);

	if ((left < m_Size) && (m_PriorityQueueData[left]->weight < m_PriorityQueueData[i_Index]->weight))
	{
		min = left;
	}
	else
	{
		min = i_Index;
	}
	
	if ((right < m_Size) && (m_PriorityQueueData[right]->weight < m_PriorityQueueData[min]->weight))
	{
		min = right;
	}

	if (min != i_Index)
	{
		swap(m_PriorityQueueData[i_Index], m_PriorityQueueData[min]);
		swap(m_indexsInPQ[m_PriorityQueueData[i_Index]->vertexIndex - 1], m_indexsInPQ[m_PriorityQueueData[min]->vertexIndex - 1]);

		FixHeap(min);
	}
}

void PriorityQueue::fixHeapBubble(int i_Index)
{
	if (i_Index && m_PriorityQueueData[Parent(i_Index)]->weight > m_PriorityQueueData[i_Index]->weight)
	{
		swap(m_indexsInPQ[m_PriorityQueueData[i_Index]->vertexIndex - 1], m_indexsInPQ[m_PriorityQueueData[Parent(i_Index)]->vertexIndex - 1]);
		swap(m_PriorityQueueData[i_Index], m_PriorityQueueData[Parent(i_Index)]);
		fixHeapBubble(Parent(i_Index));
	}
}

PriorityQueue::~PriorityQueue()
{
	for (int i = 0; i < m_PriorityQueueData.size(); i++)
	{
		delete m_PriorityQueueData[i];
	}
}

