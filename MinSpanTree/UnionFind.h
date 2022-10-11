#pragma once
#include "Graph.h"

struct Vertex
{
	int parent;
	int size;
};

class UnionFind
{
private:
	const int m_size;
	vector<Vertex> m_vertexArr;

public:
	UnionFind(int i_Size);

	void makeSet(int i_X);
	int Find(int i_X);
	void Union(int i_RepX, int i_RepY);
};

