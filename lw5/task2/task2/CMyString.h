#pragma once
#include <iostream>

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

CMyString const operator+(CMyString lhs, CMyString const& rhs);
bool operator==(CMyString const& lhs, CMyString const& rhs);
bool operator!=(CMyString const& lhs, CMyString const& rhs);

bool operator<(CMyString const& lhs, CMyString const& rhs);
bool operator>(CMyString const& lhs, CMyString const& rhs);
bool operator<=(CMyString const& lhs, CMyString const& rhs);
bool operator>=(CMyString const& lhs, CMyString const& rhs);


std::ostream& operator<<(std::ostream& stream, CMyString const& rhs);
std::istream& operator>>(std::istream& stream, CMyString& rhs);