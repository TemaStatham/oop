#pragma once
#include <cstring>
#include <iostream>

class CMyString
{
public:
	CMyString();
	CMyString(const char* pString);
	CMyString(const char* pString, size_t length);
	CMyString(CMyString const& other);
	CMyString(CMyString&& other);
	CMyString(std::string const& stlString);

	size_t GetLength() const noexcept;
	const char* GetStringData() const noexcept;
	CMyString SubString(size_t start, size_t length = SIZE_MAX) const;
	void Clear();

	CMyString& operator=(CMyString const& other);
	CMyString& operator=(std::string const& stlString);
	CMyString& operator=(CMyString&& other);
	friend CMyString operator+(CMyString const& lhs, CMyString const& rhs);
	friend CMyString operator+(std::string const& lhs, CMyString const& rhs);
	friend CMyString operator+(const char* lhs, CMyString const& rhs);
	void operator+=(CMyString const& other);
	void operator+=(std::string const& other);
	void operator+=(const char* other);
	friend bool operator==(CMyString const& lhs, CMyString const& rhs);
	friend bool operator!=(CMyString const& lhs, CMyString const& rhs);
	friend bool operator<(CMyString const& lhs, CMyString const& rhs);
	friend bool operator>(CMyString const& lhs, CMyString const& rhs);
	friend bool operator<=(CMyString const& lhs, CMyString const& rhs);
	friend bool operator>=(CMyString const& lhs, CMyString const& rhs);
	char const& operator[](size_t index) const;
	char& operator[](size_t index);
	friend std::ostream& operator<<(std::ostream& os, CMyString const& str);
	friend std::istream& operator>>(std::istream& is, CMyString& str);

	~CMyString();

private:
	void Append(CMyString const& other);
	void Append(char c);

	char* m_pData = nullptr;
	size_t m_length = 0;
};
