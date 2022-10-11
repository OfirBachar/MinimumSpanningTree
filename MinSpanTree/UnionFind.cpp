#include "UnionFind.h"

UnionFind::UnionFind(int i_Size) : m_size(i_Size)
{
	m_vertexArr.resize(i_Size);

	for(int i = 0; i < m_size; i++)
	{
		m_vertexArr[i].parent = -1;
		m_vertexArr[i].size = 0;
	}
}

void UnionFind::makeSet(int i_X)
{
	m_vertexArr[i_X - 1].parent = i_X;
	m_vertexArr[i_X - 1].size = 1;
}

int UnionFind::Find(int i_X)
{
	if (m_vertexArr[i_X - 1].parent == i_X)
	{
		return i_X;
	}
	else
	{
		return (m_vertexArr[i_X - 1].parent = Find(m_vertexArr[i_X - 1].parent));
	}
}

void UnionFind::Union(int i_RepX, int i_RepY)
{
	if (m_vertexArr[i_RepX - 1].size > m_vertexArr[i_RepY - 1].size)
	{
		m_vertexArr[i_RepY - 1].parent = i_RepX;
		m_vertexArr[i_RepX - 1].size += m_vertexArr[i_RepY - 1].size;
	}
	else
	{
		m_vertexArr[i_RepX - 1].parent = i_RepY;
		m_vertexArr[i_RepY - 1].size += m_vertexArr[i_RepX - 1].size;
	}
}
