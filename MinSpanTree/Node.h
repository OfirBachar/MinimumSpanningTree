#pragma once

class Node
{
private:
	int m_vertexIndex = 0;
	Node* m_prev;
	Node* m_next;
	int m_edgeWeight;

public:
	Node(int i_Weight, int i_Index);

	friend class List;
	friend class Graph;
};

