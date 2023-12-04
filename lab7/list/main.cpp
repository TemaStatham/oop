#include <iostream>
#include "List.hpp"

int main()
{
	/*{
		List<int> l;
		l.PushBack(1);
		std::cout << l.GetFront();
		l.PushBack(10);
		std::cout << l.GetBack();
		l.PushFront(4);
		std::cout << l.GetFront();
		l.PopFront();
		std::cout << l.GetFront();
		auto it = l.begin();
		it++;
		it = l.Erase(it);
		std::cout << l.GetBack() << (it.GetNodePtr()->data.has_value() ? it.GetNodePtr()->data.value() : 111);
		std::cout << std::endl << std::endl;
	}*/

	{
		Node<int>::NodeSpy::ResetCounts();
		List<int> list;
		//list.Clear();
		list.PushBack(1);
		list.PushBack(2);
		list.PushBack(3);
		list.Clear();

		int constructorCount = Node<int>::NodeSpy::GetConstructorCount();
		int destructorCount = Node<int>::NodeSpy::GetDestructorCount();

		std::cout << "Constructor Count: " << constructorCount << std::endl;
		std::cout << "Destructor Count: " << destructorCount << std::endl;
	}

	return 0;
}