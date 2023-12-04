#pragma once
#include <iterator>
#include <stdexcept>
#include "Node.hpp"

template <typename T>
class MyList;

template <typename T>
class ListIterator;

template <typename T>
class ConstListIterator
{
public:
	friend class MyList<T>;
	friend class ListIterator<T>;

	using iterator_category = std::bidirectional_iterator_tag;
	using difference_type = size_t;
	using value_type = const T;
	using pointer = const T*;
	using reference = const T&;

	bool operator!=(const ConstListIterator& other) const
	{
		return m_nodePtr != other.m_nodePtr;
	}

	bool operator==(const ConstListIterator& other) const
	{
		return !(*this != other);
	}

	ConstListIterator()
		: m_nodePtr(nullptr)
	{
	}

	ConstListIterator(const Node<T>* data)
		: m_nodePtr(data)
	{
	}

	ConstListIterator(const ConstListIterator& other)
		: m_nodePtr(other.m_nodePtr)
	{
	}

	~ConstListIterator() = default;

	pointer operator->() const
	{
		if (m_nodePtr == nullptr || m_nodePtr->next == nullptr || m_nodePtr->prev == nullptr)
		{
			throw std::out_of_range("iterator out of range");
		}

		return &(m_nodePtr->data);
	}

	reference operator*() const
	{
		if (m_nodePtr == nullptr || m_nodePtr->next == nullptr || m_nodePtr->prev == nullptr)
		{
			throw std::out_of_range("iterator out of range");
		}
		return m_nodePtr->data;
	}

	ConstListIterator& operator++()
	{
		if (m_nodePtr == nullptr || m_nodePtr->next == nullptr)
		{
			throw std::out_of_range("iterator out of range");
		}
		m_nodePtr = m_nodePtr->next;
		return *this;
	}

	ConstListIterator operator++(int)
	{
		if (m_nodePtr == nullptr || m_nodePtr->next == nullptr)
		{
			throw std::out_of_range("iterator out of range");
		}
		ConstListIterator tmp = *this;
		m_nodePtr = m_nodePtr->next;
		return tmp;
	}

	ConstListIterator& operator--()
	{
		if (m_nodePtr == nullptr || m_nodePtr->prev == nullptr)
		{
			throw std::out_of_range("iterator out of range");
		}
		m_nodePtr = m_nodePtr->prev;
		return *this;
	}

	ConstListIterator operator--(int)
	{
		if (m_nodePtr == nullptr || m_nodePtr->prev == nullptr)
		{
			throw std::out_of_range("iterator out of range");
		}

		ConstListIterator tmp = *this;
		m_nodePtr = m_nodePtr->prev;
		return tmp;
	}

private:
	const Node<T>* m_nodePtr;
};

template <typename T>
class ListIterator
{
public:
	friend class MyList<T>;
	friend class ConstListIterator<T>;

	using iterator_category = std::bidirectional_iterator_tag;
	using difference_type = size_t;
	using value_type = T;
	using pointer = T*;
	using reference = T&;

	bool operator!=(const ListIterator& other) const
	{
		return m_nodePtr != other.m_nodePtr;
	}

	bool operator==(const ListIterator& other) const
	{
		return !(*this != other);
	}

	ListIterator()
		: m_nodePtr(nullptr)
	{
	}

	ListIterator(Node<T>* data)
		: m_nodePtr(data)
	{
	}

	ListIterator(const ListIterator& other)
		: m_nodePtr(other.m_nodePtr)
	{
	}

	~ListIterator() = default;

	pointer operator->() const
	{
		if (m_nodePtr == nullptr || m_nodePtr->next == nullptr || m_nodePtr->prev == nullptr)
		{
			throw std::out_of_range("iterator out of range");
		}

		return &(m_nodePtr->data);
	}

	reference operator*() const
	{
		if (m_nodePtr == nullptr || m_nodePtr->next == nullptr || m_nodePtr->prev == nullptr)
		{
			throw std::out_of_range("iterator out of range");
		}
		return m_nodePtr->data;
	}

	ListIterator& operator++()
	{
		if (m_nodePtr == nullptr || m_nodePtr->next == nullptr)
		{
			throw std::out_of_range("iterator out of range");
		}
		m_nodePtr = m_nodePtr->next;
		return *this;
	}

	ListIterator operator++(int)
	{
		if (m_nodePtr == nullptr || m_nodePtr->next == nullptr)
		{
			throw std::out_of_range("iterator out of range");
		}
		ListIterator tmp = *this;
		m_nodePtr = m_nodePtr->next;
		return tmp;
	}

	ListIterator& operator--()
	{
		if (m_nodePtr == nullptr || m_nodePtr->prev == nullptr)
		{
			throw std::out_of_range("iterator out of range");
		}
		m_nodePtr = m_nodePtr->prev;
		return *this;
	}

	ListIterator operator--(int)
	{
		if (m_nodePtr == nullptr || m_nodePtr->prev == nullptr)
		{
			throw std::out_of_range("iterator out of range");
		}

		ListIterator tmp = *this;
		m_nodePtr = m_nodePtr->prev;
		return tmp;
	}

private:
	Node<T>* m_nodePtr;
};