#pragma once
#include "CIterator.h"
#include <iterator>

class CStringList
{
public:
	using Iterator = CIterator;
	using ConstIterator = std::const_iterator<CIterator>;
	using ReverseIterator = std::reverse_iterator<Iterator>;
	using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

	CStringList() = default;
	CStringList(const CStringList* list);
	CStringList(CStringList&& list);

	CStringList& operator=(CStringList&&) = default;

	CStringList(const CStringList& other);
	CStringList& operator=(const CStringList& other);

	~CStringList() noexcept;

	Iterator begin();
	Iterator end();
	ConstIterator begin() const;
	ConstIterator end() const;
	ConstIterator cbegin() const;
	ConstIterator cend() const;

	ReverseIterator rbegin();
	ReverseIterator rend();
	ConstReverseIterator rbegin() const;
	ConstReverseIterator rend() const;
	ConstReverseIterator crbegin() const;
	ConstReverseIterator crend() const;

	bool IsEmpty() const;
	operator bool() const { return !IsEmpty(); }

	size_t GetLength() const;

	CStringList& PushBack(const std::string& data);
	CStringList& PushFront(const std::string& data);

	CStringList& PopBack();
	CStringList& PopFront();

	const std::string& GetBack() const;
	const std::string& GetFront() const;

	Iterator Insert(const ListBaseIterator& where, const std::string& data);
	Iterator Erase(const ListBaseIterator& where);

	void Clear() noexcept;

private:
	NodePtr m_beginPtr = nullptr;
	NodePtr m_endPtr = nullptr;
	size_t m_length = 0;
};