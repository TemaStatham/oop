#pragma once

#include <iostream>
#include <optional>

template <typename T>
class Node
{
public:
	Node()
	{
		std::cout << "Node()" << std::endl;
	}

	Node(const T& _data)
		: data(_data)
	{
		std::cout << "Node(data)" << std::endl;
	}

	Node& operator=(const Node&) = delete;

	~Node()
	{
		std::cout << "~Node()" << std::endl;
	}

	T data;
	Node<T>* next = nullptr;
	Node<T>* prev = nullptr;
};

//private:
//	class Spy
//	{
//	private:
//		static int constructorCount;
//		static int destructorCount;
//
//	public:
//
//		Spy() : Node()
//		{
//			++constructorCount;
//		}
//
//		Spy(std::optional<T>& data) : Node(data)
//		{
//			++constructorCount;
//		}
//
//		~Spy()
//		{
//			++destructorCount;
//		}
//
//		static void ResetCounts()
//		{
//			constructorCount = 0;
//			destructorCount = 0;
//		}
//
//		static int GetConstructorCount()
//		{
//			return constructorCount;
//		}
//
//		static int GetDestructorCount()
//		{
//			return destructorCount;
//		}
//	};
//
//template<typename T>
//int Node<T>::Spy::constructorCount = 0;
//
//template<typename T>
//int Node<T>::Spy::destructorCount = 0;