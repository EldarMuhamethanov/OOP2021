#pragma once
#include <string>
#include <memory>
#include <cassert>
#include <algorithm>
#include <new>

class CStringList
{
	struct Node
	{
		Node(const std::string& data, Node* prev, Node* next)
			: data(data), prev(prev), next(next)
		{
		};
		~Node()
		{
			prev = nullptr;
			next = nullptr;
		}
		std::string data;
		Node* prev;
		Node* next;
	};
public:
	CStringList() = default;
	~CStringList();
	CStringList(CStringList const& other);
	CStringList(CStringList&& other);

	template <bool IsConst>
	class IteratorBase
	{
		friend class IteratorBase<true>;
		friend CStringList;
	public:
		using MyType = IteratorBase<IsConst>;
		using value_type = std::conditional_t<IsConst, const std::string, std::string>;
		using reference = value_type&;
		using pointer = value_type*;
		using difference_type = ptrdiff_t;
		using iterator_category = std::bidirectional_iterator_tag;

		IteratorBase() = default;
		IteratorBase(const IteratorBase<false>& other)
			: m_node(other.m_node)
		{
		}

		reference operator*() const
		{
			return m_node->data;
		}

		IteratorBase& operator++()
		{
			assert(m_node->next);
			m_node = m_node->next;
			return *this;
		}
		IteratorBase operator++(int)
		{
			return ++(*this);
		}
		IteratorBase& operator--()
		{
			assert(m_node->prev);
			m_node = m_node->prev;
			return *this;
		}
		IteratorBase operator--(int)
		{
			return --(*this);
		}
		friend bool operator==(IteratorBase const& lhs, IteratorBase const& rhs)
		{
			return lhs.m_node == rhs.m_node;
		}
		friend bool operator!=(IteratorBase const& lhs, IteratorBase const& rhs)
		{
			return lhs.m_node != rhs.m_node;
		}

	public:
		IteratorBase(Node* item)
			: m_node(item)
		{
		}

	private:
		Node* m_node = nullptr;
	};

	using iterator = IteratorBase<false>;
	using const_iterator = IteratorBase<true>;

	using reverse_iterator = std::reverse_iterator<IteratorBase<false>>;
	using const_reverse_iterator = std::reverse_iterator<IteratorBase<true>>;

	iterator begin();
	iterator end();

	const_iterator cbegin();
	const_iterator cend();

	reverse_iterator rbegin();
	reverse_iterator rend();

	const_reverse_iterator crbegin();
	const_reverse_iterator crend();

	void Clear();
	size_t GetSize()const;
	void PushFront(const std::string& data);
	void Append(const std::string& data);
	void Insert(const iterator& it, const std::string& data);
	void Insert(const reverse_iterator& it, const std::string& data);
	void Delete(const iterator& it);
	void Delete(const reverse_iterator& it);
	
	std::string& GetBackElement();
	std::string const& GetBackElement()const;

	CStringList& operator=(CStringList&& other);
	CStringList& operator=(CStringList const& other);

private:
	void CleanUp();

	size_t m_size = 0;
	Node* m_firstNode = nullptr;
	Node* m_lastNode = new Node("", nullptr, nullptr);
};