#include <cstdlib>

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

template <class Value, class Key, int numLevels>
void SkipList<Value, Key, numLevels>::remove(TypeNode * node)
{

}

template <class Value, class Key, int numLevels>
void SkipList<Value, Key, numLevels>::insert(Value value, Key key)
{

}

template <class Value, class Key, int numLevels>
SkipList<Value, Key, numLevels>::TypeNode * SkipList<Value, Key, numLevels>::findLastLessThan(Key key) const
{

}

template <class Value, class Key, int numLevels>
SkipList<Value, Key, numLevels>::TypeNode * SkipList<Value, Key, numLevels>::findFirst(Key key) const
{

}

//=============================================================================
//== End of: SkipList =========================================================
//=============================================================================
