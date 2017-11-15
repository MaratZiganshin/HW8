#include <cstdlib>
#include "SkipList.h"

//=============================================================================
//== NodeSkipList =============================================================
//=============================================================================

template <class Value, class Key, int numLevels>
void NodeSkipList<Value,Key,numLevels>::clear(void)
{
	for (int i = 0; i < numLevels; ++i)
	{
		m_nextjump[i] = 0;
	}
	m_levelHighest = -1;
}

template <class Value, class Key, int numLevels>
NodeSkipList<Value, Key, numLevels>::NodeSkipList(void)
{
	clear();
}

template <class Value, class Key, int numLevels>
NodeSkipList<Value, Key, numLevels>::NodeSkipList(Key key)
{
	clear();

	m_key = key;
}

template <class Value, class Key, int numLevels>
NodeSkipList<Value, Key, numLevels>::NodeSkipList(Key key, Value value)
{
	clear();

	m_key = key;
	m_value = value;
}
//=============================================================================
//== End of: NodeSkipList =====================================================
//=============================================================================

//=============================================================================
//== SkipList =================================================================
//=============================================================================
template <class Value, class Key, int numLevels>
SkipList<Value, Key, numLevels>::SkipList(double probability)
{
	m_probability = probability;
	for (int i = 0; i < numLevels; ++i)
	{
		// Lets use m_pPreHead as a final sentinel element
		m_pPreHead->m_nextjump[i] = m_pPreHead;
	}
	m_pPreHead->m_levelHighest = numLevels-1;
}

template<class Value, class Key, int numLevels>
NodeSkipList<Value, Key, numLevels> * SkipList<Value, Key, numLevels>::findLastLessThan(Key key) const
{
    NodeSkipList<Value, Key, numLevels>* temp = m_pPreHead;
    for (int i = m_pPreHead->m_levelHighest; i >= 0; i--)
        while (temp->m_nextjump[i] != m_pPreHead && temp->m_nextjump[i]->m_key < key)
            temp = temp->m_nextjump[i];
    while (temp->m_next != m_pPreHead && temp->m_next->m_key < key)
        temp = temp->m_next;
    return temp;
}

template<class Value, class Key, int numLevels>
NodeSkipList<Value, Key, numLevels> * SkipList<Value, Key, numLevels>::findFirst(Key key) const
{
    NodeSkipList<Value, Key, numLevels>* temp = findLastLessThan(key);
    if (temp->m_next->m_key == key)
        return temp->m_next;
    return nullptr;
}

template <class Value, class Key, int numLevels>
void SkipList<Value, Key, numLevels>::remove(TypeNode * node)
{
    NodeSkipList<Value, Key, numLevels>** listBefore = new NodeSkipList<Value, Key, numLevels>*[node->m_levelHighest + 1];
    NodeSkipList<Value, Key, numLevels>* temp = m_pPreHead;
    for (int i = node->m_levelHighest; i >= 0; i--)
    {
        while (temp->m_nextjump[i] != node && temp->m_nextjump[i]->m_key <= node->m_key)
            temp = temp->m_nextjump[i];
        listBefore[i] = temp;
    }
    while (temp->m_next != node && temp->m_next->m_key <= node->m_key)
        temp = temp->m_next;
    if (temp->m_next != node) 
        throw std::invalid_argument("Node is not found");
    for (int i = node->m_levelHighest; i >= 0; i--)
        listBefore[i]->m_nextjump[i] = node->m_nextjump[i];
    temp->m_next = node->m_next;
    delete node;
}


template <class Value, class Key, int numLevels>
void SkipList<Value, Key, numLevels>::insert(Value value, Key key)
{
    NodeSkipList<Value, Key, numLevels>* insertNode = new NodeSkipList<Value, Key, numLevels>(key, value);
    NodeSkipList<Value, Key, numLevels>** listBefore = new NodeSkipList<Value, Key, numLevels>*[m_pPreHead->m_levelHighest + 1];
    NodeSkipList<Value, Key, numLevels>* temp = m_pPreHead;

    for (int i = m_pPreHead->m_levelHighest; i >= 0; i--)
    {
        while (temp->m_nextjump[i] != m_pPreHead && temp->m_nextjump[i]->m_key < key)
            temp = temp->m_nextjump[i];
        listBefore[i] = temp;
    }
    while (temp->m_next != m_pPreHead && temp->m_next->m_key < key)
        temp = temp->m_next;
    for (int i = 0 ; i <= m_pPreHead->m_levelHighest; i++)
    {
        double random = ((double)rand() / (double)(RAND_MAX));
        if (random > m_probability)
        {
            insertNode->m_nextjump[i] = listBefore[i]->m_nextjump[i];
            listBefore[i]->m_nextjump[i] = insertNode;
        }
        else
            break;
    }
    insertNode->m_next = temp->m_next;
    temp->m_next = insertNode;
}


//=============================================================================
//== End of: SkipList =========================================================
//=============================================================================
