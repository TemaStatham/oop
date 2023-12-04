#include "CMyString.h"

constexpr char END_OF_MY_STRING = 0;
constexpr char END_OF_LINE = '\n';

CMyString::CMyString()
{
	m_pData = new char[m_length + 1];
	m_pData[0] = END_OF_MY_STRING;
}

CMyString::CMyString(const char* pString)
{
	if (pString == nullptr)
	{
		m_pData = new char[1];
		m_pData[0] = END_OF_MY_STRING;
		return;
	}
	m_length = std::strlen(pString);
	m_pData = new char[m_length + 1];
	std::memcpy(m_pData, pString, m_length + 1);
}

CMyString::CMyString(const char* pString, size_t length)
{
	if (pString == nullptr)
	{
		m_pData = new char[1];
		m_pData[0] = END_OF_MY_STRING;
		return;
	}
	m_length = length;
	m_pData = new char[m_length + 1];
	std::memcpy(m_pData, pString, m_length + 1);
	m_pData[m_length] = END_OF_MY_STRING;
}

CMyString::CMyString(CMyString const& other)
{
	m_length = other.m_length;
	m_pData = new char[m_length + 1];
	std::memcpy(m_pData, other.m_pData, m_length + 1);
}

CMyString::CMyString(CMyString&& other)
{
	// cmystring с пустым указателм на char => swap
	m_length = other.m_length;
	m_pData = new char[m_length + 1];
	std::move(other.m_pData, other.m_pData + m_length + 1, m_pData);

	other.m_pData = nullptr;
	other.m_length = 0;
}

CMyString::CMyString(std::string const& stlString)
{
	m_length = stlString.length();
	m_pData = new char[m_length + 1];
	std::memcpy(m_pData, stlString.c_str(), m_length + 1);
}

CMyString::~CMyString()
{
	// noexcept
	delete[] m_pData;
}

size_t CMyString::GetLength() const noexcept
{
	return m_length;
}

const char* CMyString::GetStringData() const noexcept
{
	return m_pData;
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
	if (start >= GetLength())
	{
		throw std::out_of_range("index out of range");
	}

	return CMyString(m_pData + start, std::min(length, m_length - start));
}

void CMyString::Clear()
{
	m_length = 0;
	delete[] m_pData;
	m_pData = nullptr;
	m_pData = new char[m_length + 1];
	m_pData[0] = END_OF_MY_STRING;
}

CMyString& CMyString::operator=(CMyString const& other)
{
	if (this != &other)
	{
		CMyString tmp(other);
		std::swap(m_pData, tmp.m_pData);
		std::swap(m_length, tmp.m_length);
	}
	return *this;
}

CMyString& CMyString::operator=(std::string const& stlString)
{
	delete[] m_pData;
	m_pData = nullptr;
	m_length = 0;

	if (!stlString.empty())
	{
		Append(CMyString(stlString));
	}

	return *this;
}

void CMyString::operator+=(CMyString const& other)
{
	Append(other);
}

void CMyString::operator+=(std::string const& other)
{
	Append(CMyString(other));
}

void CMyString::operator+=(const char* other)
{
	Append(CMyString(other));
}

CMyString operator+(CMyString const& lhs, CMyString const& rhs)
{
	CMyString newString(lhs);
	newString.Append(rhs);

	return newString;
}

CMyString operator+(std::string const& lhs, CMyString const& rhs)
{
	CMyString newString(lhs);
	newString.Append(rhs);

	return newString;
}

CMyString operator+(const char* lhs, CMyString const& rhs)
{
	CMyString newString(lhs);
	newString.Append(rhs);

	return newString;
}

bool operator==(CMyString const& lhs, CMyString const& rhs)
{
	// сначала проверить длинну
	return strcmp(lhs.GetStringData(), rhs.GetStringData()) == 0 && lhs.m_length == rhs.m_length;
}

bool operator!=(CMyString const& lhs, CMyString const& rhs)
{
	return strcmp(lhs.GetStringData(), rhs.GetStringData()) != 0 && lhs.m_length != rhs.m_length;
}

bool operator<(CMyString const& lhs, CMyString const& rhs)
{
	return strcmp(lhs.GetStringData(), rhs.GetStringData()) == -1;
}

bool operator>(CMyString const& lhs, CMyString const& rhs)
{
	return strcmp(lhs.GetStringData(), rhs.GetStringData()) == 1;
}

bool operator<=(CMyString const& lhs, CMyString const& rhs)
{
	return strcmp(lhs.GetStringData(), rhs.GetStringData()) == -1 || strcmp(lhs.GetStringData(), rhs.GetStringData()) == 0;
}

bool operator>=(CMyString const& lhs, CMyString const& rhs)
{
	return strcmp(lhs.GetStringData(), rhs.GetStringData()) == 1 || strcmp(lhs.GetStringData(), rhs.GetStringData()) == 0;
}

char const& CMyString::operator[](size_t index) const
{
	if (index < m_length)
	{
		return m_pData[index];
	}
	throw std::out_of_range("index out of range");
}

char& CMyString::operator[](size_t index)
{
	// asssert
	if (index < m_length)
	{
		return m_pData[index];
	}
	throw std::out_of_range("index out of range");
}

std::ostream& operator<<(std::ostream& os, CMyString const& str)
{
	for (size_t i = 0; i < str.m_length; i++)
	{
		os << str.m_pData[i];
	}
	return os;
}

std::istream& operator>>(std::istream& is, CMyString& str)
{
	str.Clear();

	char c;
	// buffer cltkfnm
	while (is.get(c) && c != '\n')
	{
		str.Append(c);
	}

	str.Append(END_OF_MY_STRING);

	return is;
}

CMyString& CMyString::operator=(CMyString&& other)
{
	if (this != &other)
	{
		m_pData = other.m_pData;
		m_length = other.m_length;
		other.m_pData = nullptr;
		other.m_length = 0;
	}
	return *this;
}

void CMyString::Append(CMyString const& other)
{
	if (other.m_length > 0)
	{
		char* newData = new char[m_length + other.m_length + 1];
		std::memcpy(newData, m_pData, m_length);
		std::memcpy(newData + m_length, other.m_pData, other.m_length + 1);
		delete[] m_pData;
		m_pData = newData;
		m_length += other.m_length;
	}
}

void CMyString::Append(char c)
{
	char* newData = new char[m_length + 2];
	std::memcpy(newData, m_pData, m_length);
	newData[m_length] = c;
	newData[m_length + 1] = END_OF_LINE;
	delete[] m_pData;
	m_pData = newData;
	++m_length;
}
