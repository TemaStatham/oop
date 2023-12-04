#pragma once
#include <iostream>
#include <optional>


template <typename T>
class Node
{
public:
	//переделать node spy сделать обьект которые хранят счетчсики обьект. при помози которого можно узнать как ведет себя список при вызывании исключения 
	class NodeSpy
	{
	private:
		static int constructorCount;
		static int destructorCount;

	public:
		NodeSpy()
		{
			++constructorCount;
		}

		~NodeSpy()
		{
			++destructorCount;
		}

		static void ResetCounts()
		{
			constructorCount = 0;
			destructorCount = 0;
		}

		static void SetConstructorCount()
		{
			constructorCount++;
		}

		static void SetDestructorCount()
		{
			destructorCount++;
		}

		static int GetConstructorCount()
		{
			return constructorCount;
		}

		static int GetDestructorCount()
		{
			return destructorCount;
		}
	};

	Node()
	{
		NodeSpy::SetConstructorCount();
		//std::cout << "Node()" << std::endl;
	}

	Node(const std::optional<T>& _data)
		: data(_data)
	{
		NodeSpy::SetConstructorCount();

		//std::cout << "Node(data)" << std::endl;
	}

	Node& operator=(const Node&) = delete;

	~Node()
	{
		NodeSpy::SetDestructorCount();
		//std::cout << "~Node()" << std::endl;
	}


	//прочитать про std constract_at , std::destroy_at , placment new избавиться от optional 
	//сделать буфер который 
	std::optional<T> data = std::nullopt;
	Node<T>* next = nullptr;
	Node<T>* prev = nullptr;

};

template <typename T>
struct NodeT
{
	alignas(T) char buffer[sizeof(T)];
};


template<typename T>
int Node<T>::NodeSpy::constructorCount = 0;

template<typename T>
int Node<T>::NodeSpy::destructorCount = 0;