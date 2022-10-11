#include "Node.h"

Node::Node(int i_Weight, int i_Index)
{
	m_vertexIndex = i_Index;
	m_prev = nullptr;
	m_next = nullptr;
	m_edgeWeight = i_Weight;
}

