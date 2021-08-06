#include "CMyString.h"
#include <cassert>

using namespace std;

CMyString::CMyString()
{
	m_length = 0;
	m_pChars = CreateArrayOfChar(m_length);
}
CMyString::CMyString(const char ch)
{
	m_length = 1;
	m_pChars = CreateArrayOfChar(m_length);
	if (m_pChars)
		m_pChars[0] = ch;
}
CMyString::CMyString(const char* pString)
{
	m_length = strlen(pString);
	m_pChars = CreateArrayOfChar(m_length);
	if (m_pChars)
		memcpy(m_pChars, pString, m_length);
}
CMyString::CMyString(const char* pString, size_t length)
{
	m_length = length;
	m_pChars = CreateArrayOfChar(length);
	if (m_pChars)
		memcpy(m_pChars, pString, m_length);
}
CMyString::CMyString(string const& stlString)
{
	m_length = stlString.length();
	m_pChars = CreateArrayOfChar(m_length);
	if (m_pChars)
		memcpy(m_pChars, stlString.c_str(), m_length);
}
CMyString::CMyString(CMyString const& other)
{
	m_length = other.m_length;
	m_pChars = CreateArrayOfChar(other.m_length);
	if (m_pChars)
		memcpy(m_pChars, other.GetStringData(), m_length);
}
CMyString::CMyString(CMyString&& other)
	: m_pChars(other.m_pChars)
	, m_length(other.m_length)
{ 
	other.m_pChars = nullptr;
	other.m_length = 0;
}
CMyString::~CMyString()
{
	delete[] m_pChars;
}
size_t CMyString::GetLength()const
{
	return m_length;
}
const char* CMyString::GetStringData()const
{
	return m_pChars ? m_pChars : "";
}
CMyString CMyString::SubString(size_t start, size_t length)const
{
	size_t end = min(SIZE_MAX - length < start ? SIZE_MAX : start + length, m_length);
	char* temp = CreateArrayOfChar(end - start);
	if (temp)
	{
		for (size_t index = start; index < end; index++)
		{
			temp[index - start] = m_pChars[index];
		}
		CMyString res(temp);

		delete[] temp;
		temp = nullptr;
		return res;
	}
	return "";
}
void CMyString::Clear()
{
	m_length = 0;
	delete[] m_pChars;
	m_pChars = nullptr;
}
char* CMyString::CreateArrayOfChar(size_t length) const
{
	try
	{
		char* arrayOfChar = new char[length + 1];
		arrayOfChar[length] = '\0';
		return arrayOfChar;
	}
	catch (const bad_alloc&)
	{
		return nullptr;
	}
}
CMyString& CMyString::operator+=(CMyString const& str)
{
	int newLength = m_length + str.GetLength();
	char* temp = CreateArrayOfChar(newLength);
	if (temp)
	{
		memcpy(temp, m_pChars, newLength);
		strcat(temp, str.GetStringData());
		delete[] m_pChars;
		m_pChars = temp;
		m_length = newLength;
		temp = nullptr;
	}

	return *this;
}
CMyString operator+(CMyString lhs, CMyString const& rhs)
{
	return lhs += rhs;
}
CMyString& CMyString::operator=(CMyString&& other)
{
	if (&other != this)
	{
		delete[] m_pChars;
		m_pChars = other.m_pChars;
		m_length = other.m_length;
		other.m_pChars = nullptr;
		other.m_length = 0;
	}
	return *this;
}
CMyString& CMyString::operator=(CMyString const& other)
{
	if (&other != this)
	{
		CMyString tmpCopy(other);
		swap(m_pChars, tmpCopy.m_pChars);
		swap(m_length, tmpCopy.m_length);
	}
	return *this;
}
bool operator==(CMyString const& lhs, CMyString const& rhs)
{
	if (lhs.GetLength() != rhs.GetLength())
	{
		return false;
	}
	const char* str1 = lhs.GetStringData();
	const char* str2 = rhs.GetStringData();
	for (size_t i = 0; i < lhs.GetLength(); i++)
	{
		if (str1[i] != str2[i])
			return false;
	}
	return true;
}
bool operator!=(CMyString const& lhs, CMyString const& rhs)
{
	return !(lhs == rhs);
}
bool operator<(CMyString const& lhs, CMyString const& rhs)
{
	if (lhs.GetLength() == rhs.GetLength())
	{
		const char* str1 = lhs.GetStringData();
		const char* str2 = rhs.GetStringData();
		for (size_t i = 0; i < lhs.GetLength(); i++)
		{
			if (str1[i] < str2[i])
				return false;
		}
	}
	
	return lhs.GetLength() < rhs.GetLength();
}
bool operator>(CMyString const& lhs, CMyString const& rhs)
{
	return rhs < lhs;
}
bool operator<=(CMyString const& lhs, CMyString const& rhs)
{
	return !(lhs > rhs);
}
bool operator>=(CMyString const& lhs, CMyString const& rhs)
{
	return !(lhs < rhs);
}
const char& CMyString::operator[](size_t index)const
{
	assert(index < m_length);
	return m_pChars[index];
}
char& CMyString::operator[](size_t index)
{
	assert(index < m_length);
	return m_pChars[index];
}
ostream& operator<<(ostream& stream, CMyString const& rhs)
{
	const char* str = rhs.GetStringData();
	for (size_t i = 0; i < rhs.GetLength(); i++) {
		stream << rhs[i];
	}
	return stream;
}
istream& operator>>(istream& stream, CMyString& rhs)
{
	char ch;
	while (stream.get(ch) && isspace(ch))
		rhs += ch;
	return stream;
}
CMyString::iterator CMyString::begin()
{
	return iterator(&m_pChars[0]);
}
CMyString::iterator CMyString::end()
{
	return iterator(&m_pChars[m_length]);
}
CMyString::const_iterator CMyString::cbegin()
{
	return const_iterator(&m_pChars[0]);
}
CMyString::const_iterator CMyString::cend()
{
	return const_iterator(&m_pChars[m_length]);
}
CMyString::reverse_iterator CMyString::rbegin()
{
	return reverse_iterator(end());
}
CMyString::reverse_iterator CMyString::rend()
{
	return make_reverse_iterator(begin());
}
CMyString::const_reverse_iterator CMyString::crbegin()
{
	return make_reverse_iterator(cend());
}
CMyString::const_reverse_iterator CMyString::crend()
{
	return make_reverse_iterator(cbegin());
}