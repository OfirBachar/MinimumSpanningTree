#include "List.h"


List::List()
{
	makeEmptyList(this);
}

Node* List::getHead()
{
	return m_Head;
}

void List::makeEmptyList(List* i_List)
{
	i_List->m_Head = i_List->m_Tail = nullptr;
}

void List::insertNodeToStartList(Node* i_Node)
{
	if (isEmptyList())
	{
		m_Head = m_Tail = i_Node;
	}
	else
	{
        m_Head->m_prev = i_Node;
		i_Node->m_next = m_Head;
		m_Head = i_Node;
	}
}

bool List::isEmptyList()
{
    if (m_Head == nullptr)
    {
        return true;
    }

	return false;
}

void List::deleteNode(int i_Index)
{
    Node* temp = m_Head;
    Node* prev = nullptr;

    if (temp != nullptr && temp->m_vertexIndex == i_Index)
    {
        if (temp->m_next == nullptr)
        {
            m_Head = m_Tail = nullptr;
            delete temp;

            return;
        }
        else
        {
            m_Head = temp->m_next;
            m_Head->m_prev = nullptr;
            delete temp;

            return;
        }
    }

    while (temp != nullptr && temp->m_vertexIndex != i_Index)
    {
        prev = temp;
        temp = temp->m_next;
    }

    if (temp == nullptr)
    {
        return;
    }

    if (temp == m_Tail)
    {
        m_Tail->m_prev->m_next = nullptr;
        m_Tail = m_Tail->m_prev;
    }
    else
    {
        temp->m_next->m_prev = temp->m_prev;
        prev->m_next = temp->m_next;
    }
   
    delete temp;
}

List::~List()
{
	Node* cur = m_Head;

	while (cur != nullptr)
	{
		Node* temp = cur;
		cur = cur->m_next;
		delete temp;
	}
}