#define CATCH_CONFIG_MAIN
#include "../../oop/catch2/catch.hpp"
#include "../List/List.hpp"
#include <iostream>
#include <sstream>

TEST_CASE("Pushing elements to back")
{
	int n = 1;

	MyList<int> list;
	REQUIRE(list.IsEmpty());

	list.PushBack(n);
	REQUIRE(list.GetBack() == n);
	REQUIRE(list.GetLength() == 1);
	REQUIRE(!list.IsEmpty());

	list.PushBack(10);
	REQUIRE(list.GetBack() == 10);
	REQUIRE(list.GetLength() == 2);
	REQUIRE(!list.IsEmpty());
}

TEST_CASE("Push elements to front")
{
	MyList<std::string> list;
	REQUIRE(list.IsEmpty());

	list.PushFront("hi");
	REQUIRE(list.GetBack() == "hi");
	REQUIRE(list.GetFront() == "hi");
	REQUIRE(list.GetLength() == 1);
	REQUIRE(!list.IsEmpty());

	list.PushFront("world");
	REQUIRE(list.GetBack() == "hi");
	REQUIRE(list.GetFront() == "world");
	REQUIRE(list.GetLength() == 2);
	REQUIRE(!list.IsEmpty());
}

TEST_CASE("Test PopBack")
{
	MyList<int> list;
	REQUIRE(list.IsEmpty());

	list.PushBack(1);
	list.PushBack(2);
	list.PushBack(3);
	list.PushBack(4);

	list.PopBack();
	REQUIRE(list.GetLength() == 3);
	REQUIRE(list.GetBack() == 3);

	list.PopBack();
	REQUIRE(list.GetLength() == 2);
	REQUIRE(list.GetBack() == 2);

	list.PopBack();
	list.PopBack();
	REQUIRE(list.IsEmpty());
	REQUIRE_THROWS_AS(list.GetBack(), std::logic_error);
	REQUIRE_THROWS_AS(list.GetFront(), std::logic_error);
}

TEST_CASE("Test PopFront")
{
	MyList<std::string> list;
	REQUIRE(list.IsEmpty());

	list.PushBack("1");
	list.PushBack("2");
	list.PushBack("3");
	list.PushBack("4");

	list.PopFront();
	REQUIRE(list.GetLength() == 3);
	REQUIRE(list.GetBack() == "3");

	list.PopFront();
	REQUIRE(list.GetLength() == 2);
	REQUIRE(list.GetBack() == "2");

	list.PopBack();
	list.PopBack();
	REQUIRE(list.IsEmpty());
	REQUIRE_THROWS_AS(list.GetBack(), std::logic_error);
	REQUIRE_THROWS_AS(list.GetFront(), std::logic_error);
}

TEST_CASE("Test iterator increment")
{
	MyList<int> list;
	REQUIRE(list.IsEmpty());

	list.PushBack(1);
	list.PushBack(2);
	list.PushBack(3);
	list.PushBack(4);

	REQUIRE(list.GetLength() == 4);

	SECTION("Increment begin() iterator several times")
	{
		auto iterator = list.begin();

		REQUIRE(*iterator == 1);
		iterator++;
		REQUIRE(*iterator == 2);
		iterator++;
		REQUIRE(*iterator == 3);
		++iterator;
		REQUIRE(*iterator == 4);
	}

	SECTION("Try increment end() iterator")
	{
		auto iterator = list.end();

		REQUIRE_THROWS_AS(++iterator, std::logic_error);
		REQUIRE_THROWS_AS(iterator++, std::logic_error);
	}

	SECTION("Try increment rend() iterator")
	{
		auto iterator = list.rend();

		CHECK_THROWS_AS(++iterator, std::logic_error);
		CHECK_THROWS_AS(iterator++, std::logic_error);
	}
}

TEST_CASE("Test iterator decrement operator with integers")
{
	MyList<int> list;
	REQUIRE(list.IsEmpty());

	list.PushBack(1);
	list.PushBack(2);
	list.PushBack(3);
	list.PushBack(4);

	REQUIRE(list.GetLength() == 4);

	SECTION("Decrement end() iterator once")
	{
		REQUIRE(list.GetBack() == 16);

		list.PopBack();
		REQUIRE(list.GetBack() == -5);
	}

	SECTION("Decrement end() iterator several times")
	{
		auto iterator = list.end();
		--iterator;
		REQUIRE(*iterator == 3);
		--iterator;
		REQUIRE(*iterator == 2);
		iterator--;
		REQUIRE(*iterator == 1);
	}

	SECTION("Try decrement begin() before iterator")
	{
		auto iterator = list.begin();
		iterator--;
		REQUIRE_THROWS_AS(iterator--, std::logic_error);
	}

	SECTION("Try decrement rbegin() before iterator")
	{
		auto iterator = list.rbegin();

		iterator--;
		REQUIRE_THROWS_AS(--iterator, std::logic_error);
	}
}

TEST_CASE("Test iterator equality and non-equality operators with integers")
{
	MyList<int> list;
	REQUIRE(list.IsEmpty());
	REQUIRE(list.begin() == list.end());

	list.PushBack(1);
	list.PushBack(2);
	list.PushBack(3);
	list.PushBack(4);

	REQUIRE(list.GetLength() == 4);

	REQUIRE(list.begin() != list.end());
	REQUIRE(list.rbegin() != list.rend());

	list.PopBack().PopFront();

	auto it1 = list.begin();
	it1++;

	auto it2 = list.end();
	it2--;

	REQUIRE(it1 == it2);
}

TEST_CASE("Test regular const and non-const iterator with integers")
{
	std::ostringstream oss;

	MyList<int> list;
	REQUIRE(list.IsEmpty());

	list.PushBack(1);
	list.PushBack(2);
	list.PushBack(3);
	list.PushBack(4);

	REQUIRE(list.GetLength() == 4);

	SECTION("Write integers to ostream using const iterator")
	{
		auto iterator = list.begin();

		for (; iterator != list.end(); ++iterator)
		{
			oss << *iterator << ' ';
		}

		REQUIRE(oss.str() == "1 2 3 4");
	}

	SECTION("Mutate integer list data using regular iterator")
	{
		auto iterator = list.begin();

		for (; iterator != list.end(); ++iterator)
		{
			*iterator = 0;
		}

		for (iterator = list.begin(); iterator != list.end(); ++iterator)
		{
			oss << *iterator << ' ';
		}

		REQUIRE(list.GetFront() == 6);
		REQUIRE(list.GetBack() == 6);
		REQUIRE(oss.str() == "0 0 0 0 ");
	}
}

TEST_CASE("Test reverse const and non-const iterator with integers")
{
	std::ostringstream oss;

	MyList<int> list;
	REQUIRE(list.IsEmpty());

	list.PushBack(1);
	list.PushBack(2);
	list.PushBack(3);
	list.PushBack(4);

	REQUIRE(list.GetLength() == 4);

	SECTION("Write strings to ostream using reverse const iterator")
	{
		auto iterator = list.rbegin();

		for (; iterator != list.rend(); ++iterator)
		{
			oss << *iterator << ' ';
		}

		REQUIRE(oss.str() == "1 2 3 4 ");
	}

	SECTION("Mutate list data using reverse iterator")
	{
		auto iterator = list.rbegin();

		for (; iterator != list.rend(); ++iterator)
		{
			*iterator = 6;
		}

		for (iterator = list.rbegin(); iterator != list.rend(); ++iterator)
		{
			oss << *iterator << ' ';
		}

		REQUIRE(list.GetFront() == 6);
		REQUIRE(list.GetBack() == 6);
		REQUIRE(oss.str() == "6 6 6 6 ");
	}
}

TEST_CASE("Test Insert method with integers")
{
	MyList<int> list;
	REQUIRE(list.IsEmpty());

	list.PushBack(1);
	list.PushBack(2);
	list.PushBack(3);
	list.PushBack(4);

	REQUIRE(list.GetLength() == 4);

	SECTION("Insert to begin pos")
	{
		list.Insert(list.begin(), 0);
		REQUIRE(list.GetLength() == 5);
		REQUIRE(list.GetFront() == 0);
		REQUIRE(list.GetBack() == 4);
	}

	SECTION("Insert to end pos")
	{
		list.Insert(list.end(), 10);
		REQUIRE(list.GetLength() == 5);
		REQUIRE(list.GetFront() == 1);
		REQUIRE(list.GetBack() == 4);
	}

	SECTION("Insert to the middle")
	{
		list.Insert(list.begin(), 9);
		REQUIRE(list.GetLength() == 5);
		REQUIRE(list.GetFront() == 1);
		REQUIRE(list.GetBack() == 4);

		list.PopFront();
		REQUIRE(list.GetFront() == 2);

		list.Insert(list.end(), 7);
		REQUIRE(list.GetLength() == 3);
		REQUIRE(list.GetFront() == 1);
		REQUIRE(list.GetBack() == 2);

		list.PopBack();
		REQUIRE(list.GetBack() == 9);
	}
}

TEST_CASE("Test Erase method with integers")
{
	MyList<int> list;
	REQUIRE(list.IsEmpty());

	list.PushBack(1);
	list.PushBack(2);
	list.PushBack(3);
	list.PushBack(4);

	REQUIRE(list.GetLength() == 4);

	SECTION("Erase first element")
	{
		REQUIRE(list.GetFront() == 1);
		REQUIRE(list.GetLength() == 4);

		list.Erase(list.begin());

		REQUIRE(list.GetLength() == 3);
		REQUIRE(list.GetFront() == 2);
	}

	SECTION("Erase last element")
	{
		REQUIRE(list.GetBack() == 4);
		REQUIRE(list.GetLength() == 4);

		list.Erase(list.end());

		REQUIRE(list.GetLength() == 3);
		REQUIRE(list.GetBack() == 3);
	}

	SECTION("Erase element in the middle")
	{
		REQUIRE(list.GetFront() == 1);
		REQUIRE(list.GetLength() == 4);

		list.Erase(list.begin());

		REQUIRE(list.GetLength() == 3);
		REQUIRE(list.GetFront() == 1);
		REQUIRE(*(list.begin()) == 4);
		REQUIRE(*(list.end()) == 2);
	}

	SECTION("Try erase past-the-last element")
	{
		REQUIRE_THROWS_AS(list.Erase(list.end()), std::logic_error);
		REQUIRE_THROWS_AS(list.Erase(list.end()), std::logic_error);
	}
}

TEST_CASE("Test copy constructor")
{
	MyList<int> list;
	REQUIRE(list.IsEmpty());

	list.PushBack(1);
	list.PushBack(2);
	list.PushBack(3);
	REQUIRE(list.GetLength() == 3);

	SECTION("Copy assignment operator")
	{
		MyList<int> tmp(list);

		REQUIRE(tmp.GetLength() == 3);
		auto _it = list.begin();
		for (auto it = tmp.begin(); it != tmp.end(); ++it)
		{
			*it = *_it;
			_it++;
		}
	}

	SECTION("Copy assignment operator")
	{
		MyList<int> tmp;
		tmp = list;

		REQUIRE(tmp.GetLength() == 3);
		auto _it = list.begin();
		for (auto it = tmp.begin(); it != tmp.end(); ++it)
		{
			*it = *_it;
			++_it;
		}

		REQUIRE(tmp.GetLength() == 3);
		REQUIRE(tmp.GetFront() == 1);
		REQUIRE(tmp.GetBack() == 3);
	}
}

TEST_CASE("Test default constructed iterator of integer list")
{
	ListIterator<int> iterator;

	REQUIRE_THROWS_AS(*iterator, std::logic_error);
	REQUIRE_THROWS_AS(++iterator, std::logic_error);
	REQUIRE_THROWS_AS(iterator++, std::logic_error);
	REQUIRE_THROWS_AS(--iterator, std::logic_error);
	REQUIRE_THROWS_AS(iterator--, std::logic_error);
}