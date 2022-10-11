#pragma once
using namespace std;

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <vector>

struct Edge
{
	int i;
	int j;
	int weight;

	Edge() {}
	Edge(int i_i, int i_j, int i_weight)
	{
		this->i = i_i;
		this->j = i_j;
		this->weight = i_weight;
	}
};

typedef struct Pair
{
	int weight;
	int vertexIndex;
};

enum class Color { White, Grey, Black };

// check validation input functions
void invalidInput_escape(ofstream& i_FileToPrint);
bool isValidNumOfVertices(const string& i_NumOfVertices);
bool isValidNumOfEdges(const string& i_NumOfEdges, const int i_NumOfVertices);
bool isValidEdge(float i_I, float i_J, float i_Weight, const int i_NumOfVertices);
bool isValidEdgeToDelete(float i_I, float i_J, const vector<Edge> i_Edges, const int i_NumOfVertices);
bool isNumber(const string& i_NumberStr);
bool isInGraph(float i_I, float i_J, const vector<Edge> i_Edges);

