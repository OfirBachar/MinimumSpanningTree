#include "definitions.h"


void invalidInput_escape(ofstream& i_FileToPrint)
{
	cout << "invalid input";
	i_FileToPrint << "invalid input";
	exit(1);
}

bool isValidNumOfVertices(const string& i_NumOfVertices)
{
	if (!isNumber(i_NumOfVertices) || stoi(i_NumOfVertices) < 0)
	{
		return false;
	}

	return true;
}

bool isNumber(const string& i_NumberStr)
{
	for (char const& c : i_NumberStr)
	{
		if (std::isdigit(c) == 0)
		{
			return false;
		}
	}

	return true;
}

bool isValidNumOfEdges(const string& i_NumOfEdges, const int i_NumOfVertices)
{
	if (stoi(i_NumOfEdges) < 0 || !isNumber(i_NumOfEdges))
	{
		return false;
	}

	if (stoi(i_NumOfEdges) > i_NumOfVertices * (i_NumOfVertices - 1) / 2)
	{
		return false;
	}

	return true;
} 

bool isValidEdge(float i_I, float i_J, float i_Weight, const int i_NumOfVertices)
{
	if (i_I != (int)i_I || i_I <= 0 || i_I > i_NumOfVertices ||
		i_J != (int)i_J || i_J <= 0 || i_J > i_NumOfVertices ||
		i_Weight != (int)i_Weight || i_Weight < 0)
	{
		return false;
	}
	
	return true;
}

bool isValidEdgeToDelete(float i_I, float i_J, const vector<Edge> i_Edges, const int i_NumOfVertices)
{
	if (isValidEdge(i_I, i_J, 0, i_NumOfVertices) && isInGraph(i_I, i_J, i_Edges))
	{
		return true;
	}

	return false;
}

bool isInGraph(float i_I, float i_J, const vector<Edge> i_Edges)
{
	for (int k = 0; k < i_Edges.size(); k++)
	{
		if (i_I == i_Edges[k].i && i_J == i_Edges[k].j)
		{
			return true;
		}
	}

	return false;
}