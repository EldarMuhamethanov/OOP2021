#include "CMyList.h"
#include <stdio.h>
#include <tchar.h>
#include <cassert>

using namespace std;

template<typename T>
CMyList<T>::~CMyList()
{
	Clear();
	delete m_lastNode;
	m_lastNode = nullptr;
}

template<typename T>
CMyList<T>::CMyList(CMyList const& other)
{
	try
	{
		Node* currNode = other.m_firstNode;
		while (currNode && currNode != other.m_lastNode)
		{
			Append(currNode->data);
			currNode = currNode->next;
		}
		m_size = other.m_size;
	}
	catch (const exception&)
	{
		Clear();
	}

}
template<typename T>
CMyList<T>::CMyList(CMyList&& other)
{
	Node* newLastNode = new Node("", nullptr, nullptr);
	m_firstNode = other.m_firstNode;
	m_lastNode = other.m_lastNode;
	m_size = other.m_size;

	other.m_firstNode = nullptr;
	other.m_lastNode = newLastNode;
	other.m_size = 0;
}
template<typename T>
void CMyList<T>::Clear()
{
	if (GetSize() != 0)
	{
		Node* currentNode = m_lastNode->prev;
		Node* prevNode = m_lastNode->prev;

		do
		{
			prevNode = currentNode->prev;
			delete currentNode;
			currentNode = prevNode;
		} while (currentNode);
		m_firstNode = nullptr;
		m_lastNode->prev = nullptr;
		m_size = 0;
	}
}
template<typename T>
size_t CMyList<T>::GetSize() const
{
	return m_size;
}
template<typename T>
void CMyList<T>::PushFront(const T& data)
{
	if (m_firstNode)
	{
		Node* newNode = new Node(data, nullptr, m_firstNode);
		m_firstNode->prev = newNode;
		m_firstNode = newNode;
	}
	else
	{
		Node* newNode = new Node(data, nullptr, m_lastNode);
		m_firstNode = newNode;
		m_lastNode->prev = newNode;
	}

	++m_size;
}
template<typename T>
void CMyList<T>::Append(const T& data)
{
	if (m_lastNode->prev)
	{
		Node* newNode = new Node(data, m_lastNode->prev, m_lastNode);
		m_lastNode->prev->next = newNode;
		m_lastNode->prev = newNode;
	}
	else
	{
		Node* newNode = new Node(data, nullptr, m_lastNode);
		m_firstNode = newNode;
		m_lastNode->prev = m_firstNode;
	}
	++m_size;
}
template<typename T>
void CMyList<T>::Insert(const Iterator& it, const T& data)
{
	Node* insertionNode = it.m_node;
	if (insertionNode != m_lastNode)
	{
		auto newNode = new Node(data, it.m_node->prev, it.m_node);
		insertionNode->prev->next = newNode;
		insertionNode->prev = newNode;
		++m_size;
	}
	else
	{
		Append(data);
	}
}
template<typename T>
void CMyList<T>::Insert(const reverse_iterator<Iterator>& it, const T& data)
{
	Insert(it.base(), data);
}
template<typename T>
void CMyList<T>::Delete(const Iterator& it)
{
	Node* deletionNode = it.m_node;
	if (deletionNode && deletionNode != m_lastNode)
	{
		if (deletionNode->prev)
		{
			deletionNode->prev->next = deletionNode->next;
		}
		deletionNode->next->prev = deletionNode->prev;
		if (deletionNode == m_firstNode)
			m_firstNode = deletionNode->next;

		delete deletionNode;
		--m_size;

		return;
	}
	throw exception("the node is out of the list");
}
template<typename T>
void CMyList<T>::Delete(const std::reverse_iterator<Iterator>& it)
{
	Delete(it.base());
}
template<typename T>
T& CMyList<T>::GetBackElement()
{
	assert(m_lastNode->prev);
	return m_lastNode->prev->data;
}
template<typename T>
T const& CMyList<T>::GetBackElement() const
{
	assert(m_lastNode->prev);
	return m_lastNode->prev->data;
}
template<typename T>
CMyList<T>& CMyList<T>::operator=(CMyList&& other)
{
	if (&other != this)
	{
		CMyList tmpCopy(move(other));
		return tmpCopy;
	}
	return *this;
}
template<typename T>
CMyList<T>& CMyList<T>::operator=(CMyList const& other)
{
	if (&other != this)
	{
		CMyList tmpCopy(other);
		swap(m_firstNode, tmpCopy.m_firstNode);
		swap(m_lastNode, tmpCopy.m_lastNode);
		m_size = tmpCopy.m_size;
	}
	return *this;
}
template<typename T>
typename CMyList<T>::Iterator CMyList<T>::begin()
{
	assert(m_firstNode);
	return Iterator(m_firstNode);
}
template<typename T>
typename CMyList<T>::Iterator CMyList<T>::end()
{
	assert(m_lastNode);
	return Iterator(m_lastNode);
}
template<typename T>
typename CMyList<T>::ConstIterator CMyList<T>::cbegin()
{
	assert(m_firstNode);
	return ConstIterator(m_firstNode);
}
template<typename T>
typename CMyList<T>::ConstIterator CMyList<T>::cend()
{
	assert(m_lastNode);
	return ConstIterator(m_lastNode);
}
template<typename T>
reverse_iterator<typename CMyList<T>::Iterator> CMyList<T>::rbegin()
{
	return make_reverse_iterator(end());
}
template<typename T>
reverse_iterator<typename CMyList<T>::Iterator> CMyList<T>::rend()
{
	return make_reverse_iterator(begin());
}
template<typename T>
reverse_iterator<typename CMyList<T>::ConstIterator> CMyList<T>::crbegin()
{
	return make_reverse_iterator(cend());
}
template<typename T>
reverse_iterator<typename CMyList<T>::ConstIterator> CMyList<T>::crend()
{
	return make_reverse_iterator(cbegin());
}