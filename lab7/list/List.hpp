#pragma once
#include "Iterator.hpp"

template <typename T>
class List
{
public:
	using Iterator = ListIterator<T>;
	using ConstIterator = ConstListIterator<T>;
	using ReverseIterator = std::reverse_iterator< ListIterator<T>>;
	using ConstReverseIterator = std::reverse_iterator<ConstListIterator<T>>;

	List()
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
	}

	List(List&& other) noexcept
	{
		SwapMembers(other);
	}

	List(const List& other)
		: List()
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
				//утечка памяти
				delete m_firstNode;
				delete m_lastNode;
				throw;
			}
		}
	}

	List& operator=(List&& other) noexcept
	{
		if (this != &other)
		{
			SwapMembers(other);
		}

		return *this;
	}

	List& operator=(const List& other)
	{
		if (this != &other)
		{
			List<T> tmp(other);
			SwapMembers(tmp);
		}

		return *this;
	}

	~List() noexcept
	{
		Clear();
		delete m_firstNode;
		delete m_lastNode;
	}

	Iterator begin()
	{
		return Iterator(m_firstNode->next);
	}

	Iterator end()
	{
		return Iterator(m_lastNode);
	}

	ConstIterator begin() const
	{
		return ConstIterator(m_firstNode->next);
	}

	ConstIterator end() const
	{
		return ConstIterator(m_lastNode);
	}

	ConstIterator cbegin() const
	{
		return ConstIterator(m_firstNode->next);
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
		return std::make_reverse_iterator(cend());
	}

	ConstReverseIterator rend() const
	{
		return std::make_reverse_iterator(cbegin());
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

	List& PushBack(const T& data)
	{
		Insert(end(), data);
		return *this;
	}

	List& PushFront(const T& data)
	{
		Insert(begin(), data);
		return *this;
	}

	List& PopBack()
	{
		auto it = --end();
		Erase(it);
		return *this;
	}

	List& PopFront()
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

		return m_lastNode->prev->data.value();
	}

	T& GetFront() const
	{
		if (IsEmpty())
		{
			throw std::logic_error("List is empty");
		}

		return m_firstNode->next->data.value();
	}

	Iterator Insert(const ListIterator<T>& it, const T& data)
	{
		Node<T>* newNode = new Node<T>(data);
		Node<T>* itNode = it.GetNodePtr();

		if (itNode == nullptr)
		{
			throw std::logic_error("Iterator is null");
		}

		newNode->next = itNode;
		newNode->prev = itNode->prev;
		itNode->prev->next = newNode;
		itNode->prev = newNode;

		if (itNode == m_firstNode->next)
		{
			m_firstNode->next = newNode;
		}

		++m_length;

		return Iterator(newNode);
	}

	Iterator Erase(const ListIterator<T>& it)
	{
		if (IsEmpty())
		{
			throw std::out_of_range("List is empty, erase error");
		}

		Node<T>* itNode = it.GetNodePtr();

		if (itNode == nullptr || itNode->next == nullptr || itNode->prev == nullptr)
		{
			throw std::logic_error("Iterator is null");
		}

		Node<T>* nextNode = itNode->next;
		itNode->prev->next = nextNode;
		nextNode->prev = itNode->prev;

		if (itNode == m_firstNode->next)
		{
			m_firstNode->next = nextNode;
		}

		delete itNode;
		--m_length;

		return Iterator(nextNode);
	}

	void Clear() noexcept
	{
		if (IsEmpty())
		{
			return;
		}
		Node<T>* current = m_firstNode->next;
		while (current != m_lastNode)
		{
			Node<T>* nextNode = current->next;
			delete current;
			current = nextNode;
		}

		m_firstNode->next = nullptr;
		m_lastNode = nullptr;
		m_length = 0;
	}

private:

	void SwapMembers(List<T>& other) noexcept
	{
		std::swap(m_firstNode, other.m_firstNode);
		std::swap(m_lastNode, other.m_lastNode);
		std::swap(m_length, other.m_length);
	}

	Node<T>* m_firstNode = nullptr;
	Node<T>* m_lastNode = nullptr;
	size_t m_length = 0;

};