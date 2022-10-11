#pragma once
#include "List.h"
#include "definitions.h"
#include "UnionFind.h"
#include "PriorityQueue.h"

class Graph
{
private:
	vector<List*> m_neighborsLists;

	int m_NumOfVertices;
	int m_NumOfEdges;
	vector<Edge> m_EdgesArr;
	Edge m_EdgeToRemove;

public:
	Graph(char* i_FileToReadStr, ofstream& i_FileToPrint);

	void makeEmptyGraph();
	void AddEdge(Edge i_EdgeToAdd);
	List* GetAdjList(int i_VertexIndex);
	vector<Edge> Kruskal(bool i_IsWeightsArrSort);
	void quickSort(vector<Edge>& i_EdgesArr, int i_Left, int i_Right);
	int partition(vector<Edge>& i_EdgesArr, int i_Left, int i_Right);
	void Swap(vector<Edge>& i_EdgesArr, int i_Left, int i_Right);
	int calcWeightsInParentArr(vector<Pair*> i_PArr);
	int calcWeightOfEdgeArr(vector<Edge> i_EdgeArr);
	vector<Pair*> Prim();
	bool isConnectedGraph();
	void visit(vector<Color>& i_ColorArr, int i_Vetrtex);
	void removeEdgeToRemove();
	void removeEdgeFromNighborsLists(Edge i_EdgeToDelete);
	void removeEdgeFromEdgeArr(Edge i_EdgeToDelete);
	bool addEdgeToEdgeArrFromStringstreamIfSuccess(stringstream& i_InputStringstream);
	bool addEdgeToToRemoveFromStringstreamIfSuccess(stringstream& i_InputStringstream);
	bool isAdjacent(int i_I, int i_J);
	void freeGraph();
	~Graph();
};

