#pragma once
#include <iostream>
#include <memory>
#include <cassert>

template <typename T>
class CMyArray
{
public:
	CMyArray()
	{
		m_length = 0;
		m_pElements = CreateArrayOfElements(m_length);
	}
	CMyArray(size_t length)
	{
		m_length = length;
		m_pElements = CreateArrayOfElements(length);
	}
	CMyArray(size_t length, T defaultValue)
	{
		m_length = length;
		m_pElements = CreateArrayOfElements(length);
		for (size_t i = 0; i < m_length; i++)
			m_pElements[i] = defaultValue;
	}

	CMyArray(CMyArray const& other)
	{
		T* temp = CreateArrayOfElements(other.m_length);
		if (temp)
		{
			for (size_t i = 0; i < other.m_length; i++)
				temp[i] = other.m_pElements[i];
			m_length = other.m_length;
			m_pElements = temp;
		}
	}
	CMyArray(CMyArray&& other)
	{
		m_pElements = other.m_pElements;
		m_length = other.m_length;

		other.m_pElements = nullptr;
		other.m_length = 0;
	}

	~CMyArray()
	{
		delete[] m_pElements;
	}

	size_t GetLength() const
	{
		return m_length;
	}
	void Push(T elem)
	{
		size_t newLength = m_length + 1;
		T* temp = CreateArrayOfElements(newLength);
		if (temp)
		{
			CopyArray(m_pElements, temp, m_length);
			temp[newLength - 1] = elem;
			delete[] m_pElements;
			m_pElements = temp;
			m_length = newLength;
			temp = nullptr;
		}
	}
	void Resize(size_t newLength)
	{
		T* temp = CreateArrayOfElements(newLength);
		if (temp)
		{
			CopyArray(m_pElements, temp, std::min(newLength, m_length));
			delete[] m_pElements;
			m_pElements = temp;
			m_length = newLength;
			temp = nullptr;
		}
	}

	void Clear()
	{
		T* temp = CreateArrayOfElements(0);
		delete[] m_pElements;
		m_pElements = temp;
		m_length = 0;
	}

	CMyArray& operator=(CMyArray&& other)
	{
		if (&other != this)
		{
			delete[] m_pElements;
			m_pElements = other.m_pElements;
			m_length = other.m_length;
			other.m_pElements = nullptr;
			other.m_length = 0;
		}
		return *this;
	}
	CMyArray& operator=(CMyArray const& other)
	{
		if (&other != this)
		{
			CMyArray tmpCopy(other);
			std::swap(m_pElements, tmpCopy.m_pElements);
			std::swap(m_length, tmpCopy.m_length);
		}
		return *this;
	}

	const T& operator[](size_t index)const
	{
		if (index < m_length)
		{
			return m_pElements[index];
		}
		throw std::out_of_range("index is out of range");
	}
	T& operator[](size_t index)
	{
		if (index < m_length)
		{
			return m_pElements[index];
		}
		throw std::out_of_range("index is out of range");
	}

	template <typename T>
	class CIteratorImpl
	{
		friend CMyArray;
		CIteratorImpl(T* pChar) : m_element(pChar) {};
	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using value_type = T;
		using reference = value_type&;
		using pointer = value_type*;
		using difference_type = ptrdiff_t;

		CIteratorImpl() = default;
		reference operator*()
		{
			assert(m_element);
			return *m_element;
		}
		pointer operator->()
		{
			assert(m_element);
			return m_element;
		}
		CIteratorImpl& operator+=(ptrdiff_t const& rhs)
		{
			m_element += rhs;
			return *this;
		}
		CIteratorImpl& operator-=(ptrdiff_t const& rhs)
		{
			m_element -= rhs;
			return *this;
		}
		CIteratorImpl operator+(ptrdiff_t const& rhs)
		{
			auto temp(*m_element);
			temp += rhs;
			return temp;
		}
		CIteratorImpl operator-(ptrdiff_t const& rhs)
		{
			auto temp(*m_element);
			temp -= rhs;
			return temp;
		}
		difference_type operator-(CIteratorImpl const& it)
		{
			return std::distance(it.m_element, m_element);
		}
		CIteratorImpl& operator++()
		{
			++m_element;
			return *this;
		}
		CIteratorImpl operator++(int)
		{
			++m_element;
			return *this;
		}
		CIteratorImpl& operator--()
		{
			--m_element;
			return *this;
		}
		CIteratorImpl operator--(int)
		{
			--m_element;
			return *this;
		}
		friend bool operator==(CIteratorImpl const& lhs, CIteratorImpl const& rhs)
		{
			return lhs.m_element == rhs.m_element;
		}
		friend bool operator!=(CIteratorImpl const& lhs, CIteratorImpl const& rhs)
		{
			return lhs.m_element != rhs.m_element;
		}
	private:
		T* m_element = nullptr;
	};

	class ConstIterator : public CIteratorImpl<const T>
	{
		friend CMyArray;
		ConstIterator(T* node) : CIteratorImpl<const T>(node)
		{
		}
	};
	class Iterator : public CIteratorImpl<T>
	{
		friend CMyArray;
		Iterator(T* node) : CIteratorImpl<T>(node)
		{
		}
	};

	Iterator begin()const
	{
		return Iterator(&m_pElements[0]);
	}
	Iterator end()const
	{
		return Iterator(&m_pElements[m_length]);
	}

	ConstIterator cbegin()const
	{
		return ConstIterator(&m_pElements[0]);
	}
	ConstIterator cend()const
	{
		return ConstIterator(&m_pElements[m_length]);
	}

	std::reverse_iterator<Iterator> rbegin() const
	{
		return std::make_reverse_iterator(end());
	}
	std::reverse_iterator<Iterator> rend() const
	{
		return std::make_reverse_iterator(begin());
	}
	std::reverse_iterator<ConstIterator> crbegin() const
	{
		return std::make_reverse_iterator(cend());
	}
	std::reverse_iterator<ConstIterator> crend() const
	{
		return std::make_reverse_iterator(cbegin());
	}

private:
	void CopyArray(T*& source, T*& dest, size_t length) const
	{
		for (size_t i = 0; i < length; i++)
			dest[i] = source[i];
	}

	T* CreateArrayOfElements(size_t length) const
	{
		try
		{
			T* arrayOfChar = new T[length];
			return arrayOfChar;
		}
		catch (const std::bad_alloc&)
		{
			return nullptr;
		}
	}

	T* m_pElements;
	size_t m_length = 0;
};

