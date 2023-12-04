#pragma once
#include "Iterator.hpp"

template <typename T>
class MyList
{
public:
	using Iterator = ListIterator<T>;
	using ConstIterator = ConstListIterator<T>;
	using ReverseIterator = std::reverse_iterator<Iterator>;
	using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

	MyList()
		: m_length(0)
		, m_lastNode(nullptr)
		, m_firstNode(new Node<T>())
	{
		try
		{
			m_lastNode = new Node<T>();
		}
		catch (...)
		{
			delete m_firstNode;
			throw;
		}

		m_firstNode->next = m_lastNode;
		m_lastNode->prev = m_firstNode;
		m_firstNode = m_lastNode;
	}

	MyList(MyList&& other) noexcept
	{
		std::swap(m_firstNode, other.m_firstNode);
		std::swap(m_lastNode, other.m_lastNode);
		std::swap(m_length, other.m_length);
	}

	MyList(const MyList& other)
		: MyList()
	{
		for (const T& element : other)
		{
			try
			{
				PushBack(element);
			}
			catch (...)
			{
				Clear();
				delete m_firstNode;
				delete m_lastNode;
				throw;
			}
		}
	}

	MyList& operator=(MyList&& other) noexcept
	{
		if (this != &other)
		{
			Clear();

			std::swap(m_firstNode, other.m_firstNode);
			std::swap(m_lastNode, other.m_lastNode);
			std::swap(m_length, other.m_length);
		}

		return *this;
	}

	MyList& operator=(const MyList& other)
	{
		if (this != &other)
		{
			MyList<T> tmp(other);
			Clear();
			std::swap(m_firstNode, tmp.m_firstNode);
			std::swap(m_lastNode, tmp.m_lastNode);
			std::swap(m_length, tmp.m_length);
		}

		return *this;
	}

	~MyList() noexcept
	{
		Clear();
		delete m_firstNode;
		delete m_lastNode;
	}

	Iterator begin()
	{
		return Iterator(m_firstNode);
	}

	Iterator end()
	{
		return Iterator(m_lastNode);
	}

	ConstIterator begin() const
	{
		return ConstIterator(m_firstNode);
	}

	ConstIterator end() const
	{
		return ConstIterator(m_lastNode);
	}

	ConstIterator cbegin() const
	{
		return ConstIterator(m_firstNode);
	}

	ConstIterator cend() const
	{
		return ConstIterator(m_lastNode);
	}

	ReverseIterator rbegin()
	{
		return std::make_reverse_iterator(end());
	}

	ReverseIterator rend()
	{
		return std::make_reverse_iterator(begin());
	}

	ConstReverseIterator rbegin() const
	{
		return std::make_reverse_iterator(end());
	}

	ConstReverseIterator rend() const
	{
		return std::make_reverse_iterator(begin());
	}

	ConstReverseIterator crbegin() const
	{
		return std::make_reverse_iterator(cend());
	}

	ConstReverseIterator crend() const
	{
		return std::make_reverse_iterator(cbegin());
	}

	bool IsEmpty() const noexcept
	{
		return m_length == 0;
	}

	size_t GetLength() const noexcept
	{
		return m_length;
	}

	MyList& PushBack(const T& data)
	{
		Insert(end(), data);
		return *this;
	}

	MyList& PushFront(const T& data)
	{
		Insert(begin(), data);
		return *this;
	}

	MyList& PopBack()
	{
		Erase(--end());
		return *this;
	}

	MyList& PopFront()
	{
		Erase(begin());
		return *this;
	}

	T& GetBack() const
	{
		if (IsEmpty())
		{
			throw std::logic_error("List is empty");
		}

		return m_lastNode->prev->data;
	}

	T& GetFront() const
	{
		if (IsEmpty())
		{
			throw std::logic_error("List is empty");
		}

		return m_firstNode->data;
	}

	Iterator Insert(const ListIterator<T>& it, const T& data)
	{
		Node<T>* newNode = new Node<T>(data);
		Node<T>* itNode = it.m_nodePtr;

		newNode->next = itNode;
		newNode->prev = itNode->prev;
		itNode->prev->next = newNode;
		itNode->prev = newNode;

		if (itNode == m_firstNode)
		{
			m_firstNode = newNode;
		}

		++m_length;

		return Iterator(newNode);
	}

	Iterator Erase(const ListIterator<T>& where)
	{
		if (IsEmpty())
		{
			throw std::out_of_range("List is empty, erase error");
		}

		Node<T>* wherePtr = where.m_nodePtr;

		if (wherePtr->next == nullptr || wherePtr->prev == nullptr)
		{
			throw std::logic_error("Iterator is null");
		}

		Node<T>* followingPtr = wherePtr->next;
		wherePtr->prev->next = followingPtr;
		followingPtr->prev = wherePtr->prev;

		if (wherePtr == m_firstNode)
		{
			m_firstNode = followingPtr;
		}

		Iterator nextIterator(followingPtr);
		delete wherePtr;
		--m_length;

		return nextIterator;
	}

	void Clear() noexcept
	{
		Node<T>* current = m_firstNode;
		while (current != nullptr)
		{
			Node<T>* nextNode = current->next;
			delete current;
			current = nextNode;
		}

		m_firstNode = nullptr;
		m_lastNode = nullptr;
		m_length = 0;
	}

private:
	Node<T>* m_firstNode;
	Node<T>* m_lastNode;
	size_t m_length;

};