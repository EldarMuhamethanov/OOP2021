#include <stdio.h>
#include <tchar.h>
#include "CStringList.h"
#include <cassert>
#include <stdexcept>

using namespace std;

CStringList::~CStringList()
{
	CleanUp();
}

CStringList::CStringList(CStringList const& other)
{
	try
	{
		Node* currNode = other.m_firstNode;
		while (currNode && currNode != other.m_lastNode)
		{
			Append(currNode->data);
			currNode = currNode->next;
		}
	}
	catch (...)
	{
		CleanUp();
		throw;
	}
}

CStringList::CStringList(CStringList&& other)
{
	try
	{// упростить
		Node* newLastNode = new Node("", nullptr, nullptr);
		m_firstNode = other.m_firstNode;
		delete m_lastNode;
		m_lastNode = other.m_lastNode;
		m_size = other.m_size;

		other.m_firstNode = nullptr;
		other.m_lastNode = newLastNode;
		other.m_size = 0;
	}
	catch (...)
	{
		CleanUp();
		throw;
	}
}

void CStringList::Clear()
{
	if (GetSize() != 0)
	{
		Node* currentNode = m_lastNode->prev;

		while (currentNode)
		{
			Node* oldNode = currentNode->prev;
			delete currentNode;
			currentNode = oldNode;
		}
		m_firstNode = nullptr;
		m_lastNode->prev = nullptr;
		m_size = 0;
	}
}

void CStringList::CleanUp()
{
	Clear();
	delete m_lastNode;
}

size_t CStringList::GetSize() const
{
	return m_size;
}

void CStringList::PushFront(const std::string& data)
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

void CStringList::Append(const std::string& data)
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

void CStringList::Insert(const CStringList::iterator& it, const std::string& data)
{
	Node* insertionNode = it.m_node;
	if (insertionNode)
	{
		if (insertionNode != m_lastNode) {
			auto newNode = new Node(data, it.m_node->prev, it.m_node);
			insertionNode->prev->next = newNode;
			insertionNode->prev = newNode;
		}
		else {
			Append(data);
		}
		++m_size;

		return;
	}
	throw invalid_argument("the node is out of the list");
}

void CStringList::Insert(const CStringList::reverse_iterator& it, const std::string& data)
{
	Insert(it.base(), data);
}

void CStringList::Delete(const CStringList::iterator& it)
{
	Node* deletionNode = it.m_node;
	if (deletionNode && deletionNode != m_lastNode)
	{
		if (deletionNode->prev)
			deletionNode->prev->next = deletionNode->next;

		deletionNode->next->prev = deletionNode->prev;

		if (deletionNode == m_firstNode)
			m_firstNode = deletionNode->next;

		delete deletionNode;
		--m_size;

		return;
	}
	throw invalid_argument("the node is out of the list");
}

void CStringList::Delete(const CStringList::reverse_iterator& it)
{
	Delete(it.base());
}

string& CStringList::GetBackElement()
{
	assert(m_lastNode->prev);
	return m_lastNode->prev->data;
}

string const& CStringList::GetBackElement() const
{
	assert(m_lastNode->prev);
	return m_lastNode->prev->data;
}

CStringList& CStringList::operator=(CStringList&& other)
{
	if (&other != this)
	{
		// можно просто обменять
		CStringList tmpCopy(move(other));
		swap(m_firstNode, tmpCopy.m_firstNode);
		swap(m_lastNode, tmpCopy.m_lastNode);
		swap(m_size, tmpCopy.m_size);
	}
	return *this;
}
CStringList& CStringList::operator=(CStringList const& other)
{
	if (&other != this)
	{
		CStringList tmpCopy(other);
		swap(m_firstNode, tmpCopy.m_firstNode);
		swap(m_lastNode, tmpCopy.m_lastNode);
		swap(m_size, tmpCopy.m_size);
	}
	return *this;
}

CStringList::iterator CStringList::begin()
{
	assert(m_firstNode);
	return iterator(m_firstNode);
}

CStringList::iterator CStringList::end()
{
	assert(m_lastNode);
	return iterator(m_lastNode);
}

CStringList::const_iterator CStringList::cbegin()
{
	assert(m_firstNode);
	return const_iterator(m_firstNode);
}

CStringList::const_iterator CStringList::cend()
{
	assert(m_lastNode);
	return const_iterator(m_lastNode);
}

CStringList::reverse_iterator CStringList::rbegin()
{
	return make_reverse_iterator(end());
}

CStringList::reverse_iterator CStringList::rend()
{
	return make_reverse_iterator(begin());
}

CStringList::const_reverse_iterator CStringList::crbegin()
{
	return make_reverse_iterator(cend());
}

CStringList::const_reverse_iterator CStringList::crend()
{
	return make_reverse_iterator(cbegin());
}