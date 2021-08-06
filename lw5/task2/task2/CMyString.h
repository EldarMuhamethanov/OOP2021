#pragma once
#include <iostream>
#include <memory>
#include <cassert>

class CMyString
{
public:
	CMyString();
	CMyString(const char ch);
	CMyString(const char* pString);
	CMyString(const char* pString, size_t length);
	CMyString(std::string const& stlString);

	CMyString(CMyString const& other);
	CMyString(CMyString&& other);

	~CMyString();

	template <bool IsConst>
	class IteratorBase
	{
		friend class IteratorBase<true>;
		friend CMyString;
	public:
		using MyType = IteratorBase< IsConst>;
		using value_type = std::conditional_t<IsConst, const char, char>;
		using reference = value_type&;
		using pointer = value_type*;
		using difference_type = ptrdiff_t;
		using iterator_category = std::bidirectional_iterator_tag;

		IteratorBase() = default;
		IteratorBase(const IteratorBase<false>& other)
			: m_char(other.m_char)
		{
		}

		reference operator*()
		{
			assert(m_char);
			return *m_char;
		}
		pointer operator->()
		{
			assert(m_char);
			return m_char;
		}
		IteratorBase& operator+=(ptrdiff_t const& rhs)
		{
			m_char += rhs;
			return *this;
		}
		IteratorBase& operator-=(ptrdiff_t const& rhs)
		{
			m_char -= rhs;
			return *this;
		}
		IteratorBase operator+(ptrdiff_t const& rhs)
		{
			auto temp(*m_char);
			temp += rhs;
			return temp;
		}
		IteratorBase operator-(ptrdiff_t const& rhs)
		{
			auto temp(*m_char);
			temp -= rhs;
			return temp;
		}
		difference_type operator-(IteratorBase const& it)
		{
			return std::distance(it.m_char, m_char);
		}
		IteratorBase& operator++()
		{
			++m_char;
			return *this;
		}
		IteratorBase operator++(int)
		{
			++m_char;
			return CIteratorImpl(&m_char);
		}
		IteratorBase& operator--()
		{
			--m_char;
			return *this;
		}
		IteratorBase operator--(int)
		{
			--m_char;
			return CIteratorImpl(m_char);
		}
		friend bool operator==(IteratorBase const& lhs, IteratorBase const& rhs)
		{
			return lhs.m_char == rhs.m_char;
		}
		friend bool operator!=(IteratorBase const& lhs, IteratorBase const& rhs)
		{
			return lhs.m_char != rhs.m_char;
		}

	public:
		IteratorBase(char* item)
			: m_char(item)
		{
		}

	protected:
		pointer m_char = nullptr;
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


	size_t GetLength()const;
	const char* GetStringData()const;
	CMyString SubString(size_t start, size_t length = SIZE_MAX) const;
	void Clear();

	CMyString& operator+=(CMyString const& str);

	CMyString& operator=(CMyString&& other);
	CMyString& operator=(CMyString const& other);

	const char& operator[](size_t index)const;
	char& operator[](size_t index);
private:
	char* CreateArrayOfChar(size_t length) const;

	char* m_pChars;
	size_t m_length;
};

CMyString operator+(CMyString lhs, CMyString const& rhs);
bool operator==(CMyString const& lhs, CMyString const& rhs);
bool operator!=(CMyString const& lhs, CMyString const& rhs);

bool operator<(CMyString const& lhs, CMyString const& rhs);
bool operator>(CMyString const& lhs, CMyString const& rhs);
bool operator<=(CMyString const& lhs, CMyString const& rhs);
bool operator>=(CMyString const& lhs, CMyString const& rhs);


std::ostream& operator<<(std::ostream& stream, CMyString const& rhs);
std::istream& operator>>(std::istream& stream, CMyString& rhs);