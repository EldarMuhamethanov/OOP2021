#pragma once
#include <string>
#include <memory>
#include <cassert>

template <typename T>
class CMyList
{
	struct Node
	{
		Node(T data, Node* prev, Node* next)
		{
			m_data = std::make_unique<T>(data);
			m_prev = prev;
			m_next = next;
		};
		~Node() = default;
		std::unique_ptr<T> m_data;
		Node* m_prev;
		Node* m_next;
	};
public:
	CMyList()
	{
		m_firstNode = nullptr;
		T* lastNodeData = new T;
		m_lastNode = new Node(lastNodeData, nullptr, nullptr);
	};
	~CMyList();
	CMyList(CMyList const& other);
	CMyList(CMyList&& other);

	template <typename T>
	class CIteratorImpl
	{
		friend CMyList;
		CIteratorImpl(Node* node) : m_node(node) {};
	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using value_type = T;
		using reference = value_type&;
		using pointer = value_type*;
		using difference_type = ptrdiff_t;

		CIteratorImpl() = default;
		reference operator*()
		{
			return m_node->m_data.get();
		}
		pointer operator->()
		{
			assert(m_node);
			return &m_node->m_data.get();
		}
		CIteratorImpl& operator++()
		{
			assert(m_node->m_next);
			m_node = m_node->m_next;
			return *this;
		}
		CIteratorImpl operator++(int)
		{
			assert(m_node->m_next);
			return CIteratorImpl(m_node->m_next);
		}
		CIteratorImpl& operator--()
		{
			m_node = m_node->m_prev;
			return *this;
		}
		CIteratorImpl operator--(int)
		{
			assert(m_node->m_prev);
			return CIteratorImpl(m_node->m_prev);
		}
		friend bool operator==(CIteratorImpl const& lhs, CIteratorImpl const& rhs)
		{
			return lhs.m_node == rhs.m_node;
		}
		friend bool operator!=(CIteratorImpl const& lhs, CIteratorImpl const& rhs)
		{
			return lhs.m_node != rhs.m_node;
		}
	private:
		Node* m_node = nullptr;
	};

	class ConstIterator : public CIteratorImpl<const T>
	{
		friend CMyList;
		ConstIterator(Node* node) : CIteratorImpl<const T>(node)
		{
		}
	};
	class Iterator : public CIteratorImpl<T>
	{
		friend CMyList;
		Iterator(Node* node) : CIteratorImpl<T>(node)
		{
		}
	};

	Iterator begin();
	Iterator end();

	ConstIterator cbegin();
	ConstIterator cend();

	std::reverse_iterator<Iterator> rbegin();
	std::reverse_iterator<Iterator> rend();

	std::reverse_iterator<ConstIterator> crbegin();
	std::reverse_iterator<ConstIterator> crend();

	void Clear();
	size_t GetSize()const;
	void PushFront(const T& data);
	void Append(const T& data);
	void Insert(const Iterator & it, const T& data);
	void Insert(const std::reverse_iterator<Iterator>&it, const T& data);
	void Delete(const Iterator & it);
	void Delete(const std::reverse_iterator<Iterator>&it);

	T& GetBackElement();
	T const& GetBackElement()const;


	CMyList& operator=(CMyList&& other);
	CMyList& operator=(CMyList const& other);

private:
	size_t m_size = 0;
	Node* m_firstNode;
	Node* m_lastNode;
};

