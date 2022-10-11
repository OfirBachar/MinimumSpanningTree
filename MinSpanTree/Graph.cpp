#include "Graph.h"


Graph::Graph(char* i_FileToReadStr, ofstream& i_FileToPrint)
{
	ifstream fileToRead(i_FileToReadStr, ios::in);

	if (!fileToRead.is_open())
	{
		cout << "Can not open file to read.";
		i_FileToPrint << "Can not open file to read.";
		exit(1);
	}

	string inputString;

	getline(fileToRead, inputString);

	if (!isValidNumOfVertices(inputString))
	{
		invalidInput_escape(i_FileToPrint);
	}

	m_NumOfVertices = stoi(inputString);

	getline(fileToRead, inputString);

	if (!isValidNumOfEdges(inputString, m_NumOfVertices))
	{
		invalidInput_escape(i_FileToPrint);
	}

	m_NumOfEdges = stoi(inputString);

	for (int i = 0; i < m_NumOfEdges; i++)
	{
		getline(fileToRead, inputString);
		stringstream inputStringstream(inputString);

		if (!addEdgeToEdgeArrFromStringstreamIfSuccess(inputStringstream))
		{
			invalidInput_escape(i_FileToPrint);
		}
	}

	getline(fileToRead, inputString);
	stringstream inputStringstream(inputString);

	if (!addEdgeToToRemoveFromStringstreamIfSuccess(inputStringstream))
	{
		invalidInput_escape(i_FileToPrint);
	}

	getline(fileToRead, inputString);
	
	if (fileToRead.peek() != EOF)
	{
		invalidInput_escape(i_FileToPrint);
	}

	fileToRead.close();

	makeEmptyGraph();

	for (int i = 0; i < m_NumOfEdges; i++)
	{
		this->AddEdge(m_EdgesArr[i]);
	}
}

bool Graph::addEdgeToEdgeArrFromStringstreamIfSuccess(stringstream& i_InputStringstream)
{
	string inputStringI, inputStringJ, inputStringW;
	Edge edgeToAdd;

	if (i_InputStringstream >> inputStringI && isNumber(inputStringI) &&
		i_InputStringstream >> inputStringJ && isNumber(inputStringJ) &&
		i_InputStringstream >> inputStringW && isNumber(inputStringW))
		{
		float i = stof(inputStringI);
		float j = stof(inputStringJ);
		float weight = stof(inputStringW);

		if (isValidEdge(i, j, weight, m_NumOfVertices) && !isInGraph(i, j, m_EdgesArr))
		{
			edgeToAdd.i = i;
			edgeToAdd.j = j;
			edgeToAdd.weight = weight;
			m_EdgesArr.push_back(edgeToAdd);	
		}
		else
		{
			return false;
		}

		return true;
	}

	return false;
}

bool Graph::isAdjacent(int i, int j)
{
	bool isAdjacentResult = false;
	List* lstToCheck = m_neighborsLists[i - 1];
	Node* current = lstToCheck->getHead();

	while (current != nullptr)
	{
		if (current->m_vertexIndex == j)
		{
			isAdjacentResult = true;
			break;
		}
		else
		{
			current = current->m_next;
		}
	}

	return isAdjacentResult;
}

bool Graph::addEdgeToToRemoveFromStringstreamIfSuccess(stringstream& i_InputStringstream)
{
	string inputStringI, inputStringJ, inputStringW;
	Edge edgeToAdd;

	if (i_InputStringstream >> inputStringI && isNumber(inputStringI) &&
		i_InputStringstream >> inputStringJ && isNumber(inputStringJ))
	{
		float i = stof(inputStringI);
		float j = stof(inputStringJ);

		if (isValidEdgeToDelete(i, j, m_EdgesArr, m_NumOfVertices) && !(i_InputStringstream >> inputStringW))
		{
			m_EdgeToRemove.i = i;
			m_EdgeToRemove.j = j;
			m_EdgeToRemove.weight = 0;
		}
		else
		{
			return false;
		}

		return true;
	}

	return false;
}

void Graph::makeEmptyGraph()
{
	for(int i = 0; i < m_NumOfVertices; i++)
	{
		List* ListOfVertice = new List;
		m_neighborsLists.push_back(ListOfVertice);
	}
}

List* Graph::GetAdjList(int i_VertexIndex)
{
	return m_neighborsLists[i_VertexIndex - 1];
}

void Graph::AddEdge(Edge i_EdgeToAdd)
{
	Node* vertexjToAdd = new Node(i_EdgeToAdd.weight, i_EdgeToAdd.j);
	m_neighborsLists[i_EdgeToAdd.i - 1]->insertNodeToStartList(vertexjToAdd);
	Node* vertexiToAdd = new Node(i_EdgeToAdd.weight, i_EdgeToAdd.i);
	m_neighborsLists[i_EdgeToAdd.j - 1]->insertNodeToStartList(vertexiToAdd);
}

vector<Edge> Graph::Kruskal(bool i_IsWeightsArrSort)
{
	if (!i_IsWeightsArrSort)
	{
		quickSort(m_EdgesArr, 0, m_NumOfEdges - 1);
	}

	UnionFind UF(m_NumOfVertices);

	vector<Edge> minSpanTreeEdges;

	for (int i = 1; i <= m_NumOfVertices; i++)
	{
		UF.makeSet(i);
	}

	for (int i = 0; i < m_NumOfEdges; i++)
	{
		int repI = UF.Find(m_EdgesArr[i].i);
		int repJ = UF.Find(m_EdgesArr[i].j);

		if (repI != repJ)
		{
			minSpanTreeEdges.push_back(m_EdgesArr[i]);
		}

			UF.Union(repI, repJ);
	}

	return minSpanTreeEdges;
}

void Graph::quickSort(vector<Edge>& i_EdgesArr, int i_Left, int i_Right)
{
	int pivotIndex;

	if (i_Left < i_Right)
	{
		pivotIndex = partition(i_EdgesArr, i_Left, i_Right);
		quickSort(i_EdgesArr, i_Left, pivotIndex - 1);
		quickSort(i_EdgesArr, pivotIndex + 1, i_Right);
	}
}

int Graph::partition(vector<Edge>& i_EdgesArr, int i_Left, int i_Right)
{
	int pivot = i_EdgesArr[i_Left].weight;
	int count = 0;

	for (int i = i_Left + 1; i <= i_Right; i++)
	{
		if (i_EdgesArr[i].weight <= pivot)
			count++;
	}

	int pivotIndex = i_Left + count;

	Swap(i_EdgesArr, pivotIndex, i_Left);

	int leftPivot = i_Left;
	int rightPivot = i_Right;

	while (leftPivot < pivotIndex && rightPivot > pivotIndex)
	{
		while (i_EdgesArr[leftPivot].weight <= pivot)
		{
			leftPivot++;
		}

		while (i_EdgesArr[rightPivot].weight > pivot)
		{
			rightPivot--;
		}

		if (leftPivot < pivotIndex && rightPivot > pivotIndex)
		{
			Swap(i_EdgesArr, leftPivot, rightPivot);
			leftPivot++;
			rightPivot--;
		}
	}

	return pivotIndex;
}

void Graph::Swap(vector<Edge>& i_EdgesArr, int i_Left, int i_Right)
{
	Edge temp = i_EdgesArr[i_Left];
	i_EdgesArr[i_Left] = i_EdgesArr[i_Right];
	i_EdgesArr[i_Right] = temp;
}

int Graph::calcWeightOfEdgeArr(vector<Edge> i_EdgesArr)
{
	int weightOfGraph = 0;

	for (int i = 0; i < i_EdgesArr.size(); i++)
	{
		weightOfGraph += i_EdgesArr[i].weight;
	}

	return weightOfGraph;
}

vector<Pair*> Graph::Prim()
{
	int numOfVertices = m_NumOfVertices;
	PriorityQueue PQ(numOfVertices);
	vector<bool> InT(numOfVertices, false);

	vector<Pair*> min(numOfVertices);
	vector<Pair*> P(numOfVertices, nullptr);

	for (int i = 0; i < numOfVertices; i++)
	{
		min[i] = new Pair;
		min[i]->vertexIndex = i + 1;
		min[i]->weight = INT32_MAX;
	}

	min[0]->weight = 0;
	PQ.Build(min);

	Pair* minWeightVertex;

	while (!PQ.IsEmpty())
	{
		minWeightVertex = PQ.DeleteMin();
		InT[minWeightVertex->vertexIndex - 1] = true;
		List* adjList = GetAdjList(minWeightVertex->vertexIndex);
		Node* curHeadAdjList = adjList->getHead();

		while (curHeadAdjList != nullptr)
		{
			if (!InT[curHeadAdjList->m_vertexIndex - 1] && curHeadAdjList->m_edgeWeight < min[curHeadAdjList->m_vertexIndex - 1]->weight)
			{
				min[curHeadAdjList->m_vertexIndex - 1]->weight = curHeadAdjList->m_edgeWeight;
				P[curHeadAdjList->m_vertexIndex - 1] = minWeightVertex;
				PQ.DecreaseKey(PQ.m_indexsInPQ[curHeadAdjList->m_vertexIndex - 1], curHeadAdjList->m_edgeWeight);
			}

			curHeadAdjList = curHeadAdjList->m_next;
		}
	}

	return P;
}

int Graph::calcWeightsInParentArr(vector<Pair*> i_PArr)
{
	int sumOfEdgesWeights = 0;
	int numOfVertices = i_PArr.size();

	Node* curHeadOfAdjList;

	for (int i = 1; i < numOfVertices; i++)
	{
		curHeadOfAdjList = GetAdjList(i + 1)->getHead();

		while (curHeadOfAdjList->m_vertexIndex != i_PArr[i]->vertexIndex)
		{
			curHeadOfAdjList = curHeadOfAdjList->m_next;
		}
		sumOfEdgesWeights += curHeadOfAdjList->m_edgeWeight;
	}

	return sumOfEdgesWeights;
}

bool Graph::isConnectedGraph()
{
	vector<Color> colorArr(m_NumOfVertices, Color::White);
	visit(colorArr, 0);

	for (int i = 0; i < m_NumOfVertices; i++)
	{
		if (colorArr[i] != Color::Black)
		{
			return false;
		}
	}

	return true;
}

void Graph::visit(vector<Color>& i_ColorArr, int i_Vetrtex)
{
	i_ColorArr[i_Vetrtex] = Color::Grey;
	Node* curHeadOfAdjList = GetAdjList(i_Vetrtex + 1)->getHead();

	while (curHeadOfAdjList != nullptr)
	{
		if (i_ColorArr[curHeadOfAdjList->m_vertexIndex - 1] == Color::White)
		{
			visit(i_ColorArr, curHeadOfAdjList->m_vertexIndex - 1);
		}

		curHeadOfAdjList = curHeadOfAdjList->m_next;
	}

	i_ColorArr[i_Vetrtex] = Color::Black;
}

void Graph::removeEdgeToRemove()
{
	removeEdgeFromNighborsLists(m_EdgeToRemove);
	removeEdgeFromEdgeArr(m_EdgeToRemove);
}

void Graph::removeEdgeFromNighborsLists(Edge i_EdgeToDelete)
{
	m_neighborsLists[i_EdgeToDelete.i - 1]->deleteNode(i_EdgeToDelete.j);
	m_neighborsLists[i_EdgeToDelete.j - 1]->deleteNode(i_EdgeToDelete.i);
}

void Graph::removeEdgeFromEdgeArr(Edge i_EdgeToDelete)
{
	for (int i = 0; i < m_NumOfEdges; i++)
	{
		if ((m_EdgesArr[i].i == i_EdgeToDelete.i && m_EdgesArr[i].j == i_EdgeToDelete.j) ||
			(m_EdgesArr[i].i == i_EdgeToDelete.j && m_EdgesArr[i].j == i_EdgeToDelete.i))
		{
			m_EdgesArr.erase(m_EdgesArr.begin() + i);
			break;
		}
	}

	m_NumOfEdges--;
}

void Graph::freeGraph()
{
	for (int i = 0; i < m_NumOfVertices; i++)
	{
		delete m_neighborsLists[i];
	}
}

Graph::~Graph()
{
	freeGraph();
}