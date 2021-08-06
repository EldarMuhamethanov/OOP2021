#pragma once
#include <string>
#include <memory>
#include <cassert>
#include <algorithm>
#include <new>
#include <stdexcept>

template <typename T>
class CMyArray
{
	template <bool IsConst>
	class IteratorBase
	{
		friend class IteratorBase<true>;
	public:
		using MyType = IteratorBase<IsConst>;
		using value_type = std::conditional_t<IsConst, const T, T>;
		using reference = value_type&;
		using pointer = value_type*;
		using difference_type = ptrdiff_t;
		using iterator_category = std::bidirectional_iterator_tag;

		IteratorBase() = default;
		IteratorBase(const IteratorBase<false>& other)
			: m_item(other.m_item)
		{
		}

		reference& operator*() const
		{
			return *m_item;
		}

		MyType& operator+=(difference_type offset)
		{
			m_item += offset;
			return *this;
		}
		MyType& operator-=(difference_type offset)
		{
			m_item -= offset;
			return *this;
		}
		MyType& operator++()
		{
			++m_item;
			return *this;
		}
		MyType& operator--()
		{
			--m_item;
			return *this;
		}
		MyType operator+(difference_type offset) const
		{
			MyType self(m_item);
			return self += offset;
		}
		MyType operator-(difference_type offset) const
		{
			MyType self(m_item);
			return self -= offset;
		}
		MyType operator++(int)
		{
			return ++(*this);
		}
		MyType operator--(int)
		{
			return --(*this);
		}
		friend MyType operator+(difference_type offset, const MyType& it)
		{
			return it + offset;
		}
		friend bool operator==(MyType const& lhs, MyType const& rhs)
		{
			return lhs.m_item == rhs.m_item;
		}
		friend bool operator!=(MyType const& lhs, MyType const& rhs)
		{
			return lhs.m_item != rhs.m_item;
		}

	public:
		IteratorBase(T* item)
			: m_item(item)
		{
		}

	protected:
		T* m_item = nullptr;
	};

public:
	CMyArray() = default;

	CMyArray(const CMyArray& arr)
	{
		const auto size = arr.GetSize();
		if (size != 0)
		{
			m_begin = RawAlloc(size);
			m_end = m_begin;
			try
			{
				CopyItems(arr.m_begin, arr.m_end, m_begin, m_end);
				m_endOfCapacity = m_end;
			}
			catch (...)
			{
				DeleteItems(m_begin, m_end);
				throw;
			}
		}
	}
	CMyArray(CMyArray&& other)// переместить данные, оставить other в валидном
	{
		const auto size = other.GetSize();
		if (size != 0)
		{
			DeleteItems(m_begin, m_end);
			m_begin = other.m_begin;
			m_end = other.m_end;
			m_endOfCapacity = other.m_endOfCapacity;

			other.m_begin = nullptr;
			other.m_end = nullptr;
			other.m_endOfCapacity = nullptr;
		}
	}

	void Clear()
	{
		DeleteItems(m_begin, m_end);
		m_begin = RawAlloc(0);
		// не менять capacity
		m_end = m_begin;
	}

	void Append(const T& value)
	{
		if (m_end == m_endOfCapacity) // no free space
		{
			size_t newCapacity = std::max(size_t(1), GetCapacity() * 2);

			auto newBegin = RawAlloc(newCapacity);
			T* newEnd = newBegin;
			try
			{
				CopyItems(m_begin, m_end, newBegin, newEnd);
				// Конструируем копию value по адресу newItemLocation
				new (newEnd) T(value);
				++newEnd;
			}
			catch (...)
			{
				DeleteItems(newBegin, newEnd);
				throw;
			}
			DeleteItems(m_begin, m_end);

			// Переключаемся на использование нового хранилища элементов
			m_begin = newBegin;
			m_end = newEnd;
			m_endOfCapacity = m_begin + newCapacity;
		}
		else // has free space
		{
			new (m_end) T(value);
			++m_end;
		}
	}

	void Resize(size_t newSize)
	{
		size_t currentSize = GetSize();
		// при уменьшеннии просто удалить излишние
		if (newSize != currentSize)
		{
			if (newSize < currentSize)
			{
				DestroyItems(m_begin + newSize - 1, m_end);
				m_end = m_begin + newSize;
			}
			else
			{
				auto newBegin = RawAlloc(newSize);
				T* newEnd = newBegin;
				try
				{
					CopyItems(m_begin, m_begin + newSize, newBegin, newEnd);
					for (size_t i = currentSize; i < newSize; i++)
					{
						new (newEnd) T();
						newEnd++;
					}
				}
				catch (...)
				{
					DeleteItems(newBegin, newEnd);
					throw;
				}
				DeleteItems(m_begin, m_end);

				// Переключаемся на использование нового хранилища элементов
				m_begin = newBegin;
				m_end = newEnd;
				m_endOfCapacity = newEnd;
			}
		}
	}

	T& GetBack()
	{
		assert(GetSize() != 0u);
		return m_end[-1];
	}

	const T& GetBack() const
	{
		assert(GetSize() != 0u);
		return m_end[-1];
	}

	size_t GetSize() const
	{
		return m_end - m_begin;
	}

	size_t GetCapacity() const
	{
		return m_endOfCapacity - m_begin;
	}
	~CMyArray()
	{
		DeleteItems(m_begin, m_end);
	}

	const T& operator[](size_t index)const
	{
		if (index < GetSize())
		{
			return m_begin[index];
		}
		throw std::out_of_range("index is out of range");
	}
	T& operator[](size_t index)
	{
		if (index < GetSize())
		{
			return m_begin[index];
		}
		throw std::out_of_range("index is out of range");
	}

	CMyArray& operator=(CMyArray&& other)// нет теста
	{
		if (&other != this)
		{
			DeleteItems(m_begin, m_end);
			m_begin = other.m_begin;
			m_end = other.m_end;
			m_endOfCapacity = other.m_endOfCapacity;
			
			other.m_begin = nullptr;
			other.m_end = nullptr;
			other.m_endOfCapacity = nullptr;
		}
		return *this;
	}
	CMyArray& operator=(CMyArray const& other)
	{
		if (&other != this)
		{
			CMyArray tmpCopy(other);
			std::swap(m_begin, tmpCopy.m_begin);
			std::swap(m_end, tmpCopy.m_end);
			std::swap(m_endOfCapacity, tmpCopy.m_endOfCapacity);
		}
		return *this;
	}

	using iterator = IteratorBase<false>;
	using const_iterator = IteratorBase<true>;

	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	// добавить константные методы
	iterator begin() const
	{
		return iterator(m_begin);
	}
	iterator end() const
	{
		return iterator(m_end);
	}
	const_iterator cbegin() const
	{
		return const_iterator(m_begin);
	}
	const_iterator cend() const
	{
		return const_iterator(m_end);
	}
	reverse_iterator rbegin() const
	{
		return std::make_reverse_iterator(end());
	}
	reverse_iterator rend() const
	{
		return std::make_reverse_iterator(begin());
	}
	const_reverse_iterator crbegin() const
	{
		return std::make_reverse_iterator(end());
	}
	const_reverse_iterator crend() const
	{
		return std::make_reverse_iterator(begin());
	}
private:
	static void DeleteItems(T* begin, T* end)
	{
		// Разрушаем старые элементы
		DestroyItems(begin, end);
		// Освобождаем область памяти для их хранения
		RawDealloc(begin);
	}

	// Копирует элементы из текущего вектора в to, возвращает newEnd
	static void CopyItems(const T* srcBegin, const T* srcEnd, T* const dstBegin, T*& dstEnd)
	{
		for (dstEnd = dstBegin; srcBegin != srcEnd; ++srcBegin, ++dstEnd)
		{
			// Construct "T" at "dstEnd" as a copy of "*begin"
			new (dstEnd) T(*srcBegin);
		}
	}

	static void DestroyItems(T* from, T* to)
	{
		// dst - адрес объект, при конструирование которого было выброшено исключение
		// to - первый скорнструированный объект
		while (to != from)
		{
			--to;
			// явно вызываем деструктор для шаблонного типа T
			to->~T();
		}
	}

	static T* RawAlloc(size_t n)
	{
		size_t memSize = n * sizeof(T);
		T* p = static_cast<T*>(malloc(memSize));
		if (!p)
		{
			throw std::bad_alloc();
		}
		return p;
	}

	static void RawDealloc(T* p)
	{
		if (p)
		{
			free(p);
		}
	}

private:
	T* m_begin = nullptr;
	T* m_end = nullptr;
	T* m_endOfCapacity = nullptr;
};
