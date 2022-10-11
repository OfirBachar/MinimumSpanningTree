#pragma once
#include "Node.h"

class List
{
private:
	Node* m_Head;
	Node* m_Tail;

public:
	List();

	Node* getHead();
	void makeEmptyList(List* i_List);
	void insertNodeToStartList(Node* i_Node);
	bool isEmptyList();
	void deleteNode(int i_Index);
	~List();
};

