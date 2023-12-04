#pragma once
#include <iterator>
#include <stdexcept>
#include "Node.hpp"

template <typename T>
class List;

template <typename T>
class BaseIterator
{
public:
	friend class List<T>;
	using iterator_category = std::bidirectional_iterator_tag;
	using difference_type = std::ptrdiff_t;

	bool operator!=(const BaseIterator& other) const
	{
		return (m_nodePtr != other.GetNodePtr());
	}

	bool operator==(const BaseIterator& other) const
	{
		return !(*this != other);
	}

	BaseIterator()
		: m_nodePtr(nullptr)
	{
	}

	BaseIterator(Node<T>* data)
		: m_nodePtr(data)
	{
	}

	~BaseIterator() = default;

	T* operator->() const
	{
		if (m_nodePtr == nullptr || m_nodePtr->next == nullptr || m_nodePtr->prev == nullptr)
		{
			throw std::out_of_range("iterator out of range");
		}

		return &(m_nodePtr->data.value());
	}

	T& operator*() const
	{
		if (m_nodePtr == nullptr || m_nodePtr->next == nullptr || m_nodePtr->prev == nullptr)
		{
			throw std::out_of_range("iterator out of range");
		}

		return m_nodePtr->data.value();
	}

	void operator++()
	{
		if (m_nodePtr == nullptr || m_nodePtr->next == nullptr)
		{
			throw std::out_of_range("iterator out of range");
		}
		m_nodePtr = m_nodePtr->next;
	}

	Node<T>* operator++(int)
	{
		if (m_nodePtr == nullptr || m_nodePtr->next == nullptr)
		{
			throw std::out_of_range("iterator out of range");
		}
		Node<T>* tmp = m_nodePtr;
		m_nodePtr = m_nodePtr->next;

		return tmp;
	}

	void operator--()
	{
		if (m_nodePtr == nullptr || m_nodePtr->prev == nullptr || m_nodePtr->prev->prev == nullptr)
		{
			throw std::out_of_range("iterator out of range");
		}
		m_nodePtr = m_nodePtr->prev;
	}

	Node<T>* operator--(int)
	{
		if (m_nodePtr == nullptr || m_nodePtr->prev == nullptr || m_nodePtr->prev->prev == nullptr)
		{
			throw std::out_of_range("iterator out of range");
		}

		Node<T>* tmp = m_nodePtr;
		m_nodePtr = m_nodePtr->prev;

		return tmp;
	}

	Node<T>* GetNodePtr() const
	{
		return m_nodePtr;
	}

protected:
	Node<T>* m_nodePtr;
};

template <typename T>
class ConstListIterator;

template <typename T>
class BaseIterator;

template <typename T>
class ListIterator : public BaseIterator<T>
{
public:
	friend class ConstListIterator<T>;

	using value_type = T;
	using pointer = value_type*;
	using reference = value_type&;

	ListIterator()
		:BaseIterator<T>()
	{
	}

	ListIterator(Node<T>* data)
		:BaseIterator<T>(data)
	{
	}

	~ListIterator() = default;

	pointer operator->() const
	{
		return BaseIterator<T>::operator->();
	}

	reference operator*() const
	{
		return BaseIterator<T>::operator*();
	}

	ListIterator& operator++()
	{
		BaseIterator<T>::operator++();
		return *this;
	}

	ListIterator operator++(int)
	{
		return ListIterator(BaseIterator<T>::operator++(1));
	}

	ListIterator& operator--()
	{
		BaseIterator<T>::operator--();
		return *this;
	}

	ListIterator operator--(int)
	{
		return ListIterator(BaseIterator<T>::operator--(1));
	}

	Node<T>* GetNodePtr() const
	{
		return BaseIterator<T>::GetNodePtr();
	}
};


//уменьшить дублирование кода - уменьшил
template <typename T>
class BaseIterator;

template <typename T>
class ConstListIterator : public BaseIterator<T>
{
public:

	using value_type = const T;
	using pointer = const  value_type*;
	using reference = const value_type&;

	bool operator!=(const BaseIterator<T>& other) const
	{
		return BaseIterator<T>::operator!=(other);
	}

	bool operator==(const BaseIterator<T>& other) const
	{
		return !(*this != other);
	}

	ConstListIterator()
		: BaseIterator<T>()
	{
	}

	ConstListIterator(Node<T>* data)
		: BaseIterator<T>(data)
	{
	}

	~ConstListIterator() = default;

	const pointer operator->() const
	{
		return BaseIterator<T>::operator->();
	}

	const reference operator*() const
	{
		return BaseIterator<T>::operator*();
	}

	ConstListIterator<T> operator++()
	{
		BaseIterator<T>::operator++();
		return *this;
	}

	ConstListIterator<T> operator++(int)
	{
		return ConstListIterator(BaseIterator<T>::operator++(1));
	}

	ConstListIterator<T>& operator--()
	{
		BaseIterator<T>::operator--();
		return *this;
	}

	ConstListIterator<T> operator--(int)
	{
		return ConstListIterator(BaseIterator<T>::operator--(1));
	}

	Node<T>* GetNodePtr() const
	{
		return BaseIterator<T>::GetNodePtr();
	}
};

//std::enable if уменьшить дублирование кода /
//должна быть возможность создать const iterator из не конст итератор а наоборот не должна быть