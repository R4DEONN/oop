#include "catch2/catch_test_macros.hpp"
#include "StringList.h"

TEST_CASE("CStringList Default Constructor", "[CStringList]") {
	CStringList list;
	REQUIRE(list.isEmpty());
	REQUIRE(list.GetSize() == 0);
}

TEST_CASE("CStringList PushFrontAndBack", "[CStringList]") {
	CStringList list;
	list.PushFront("world");
	list.PushFront("hello");
	list.PushBack("!");

	REQUIRE(list.GetSize() == 3);

	auto it = list.Begin();
	REQUIRE(*it++ == "hello");
	REQUIRE(*it++ == "world");
	REQUIRE(*it == "!");
}

TEST_CASE("CStringList Copy Constructor", "[CStringList]") {
	CStringList list;
	list.PushBack("hello");
	list.PushBack("world");

	CStringList copyList = list;
	REQUIRE(copyList.GetSize() == 2);

	auto it = copyList.Begin();
	REQUIRE(*it++ == "hello");
	REQUIRE(*it == "world");
}

// Test move constructor
TEST_CASE("CStringList Move Constructor", "[CStringList]") {
	CStringList list;
	list.PushBack("hello");
	list.PushBack("world");

	CStringList moveList = std::move(list);
	REQUIRE(moveList.GetSize() == 2);
	REQUIRE(list.isEmpty());
}

TEST_CASE("CStringList Copy Assignment", "[CStringList]") {
	CStringList list;
	list.PushBack("hello");
	list.PushBack("world");

	CStringList copyList;
	copyList = list;
	REQUIRE(copyList.GetSize() == 2);

	auto it = copyList.Begin();
	REQUIRE(*it++ == "hello");
	REQUIRE(*it == "world");
}

TEST_CASE("CStringList Move Assignment", "[CStringList]") {
	CStringList list;
	list.PushBack("hello");
	list.PushBack("world");

	CStringList moveList;
	moveList = std::move(list);
	REQUIRE(moveList.GetSize() == 2);
	REQUIRE(list.isEmpty());
}

TEST_CASE("CStringList Clear", "[CStringList]") {
	CStringList list;
	list.PushBack("hello");
	list.PushBack("world");

	list.ClearList();
	REQUIRE(list.isEmpty());
	REQUIRE(list.GetSize() == 0);
}

TEST_CASE("CStringList Insert", "[CStringList]") {
	CStringList list;
	list.PushBack("hello");
	list.PushBack("world");

	auto it = list.Begin();
	++it;
	list.Insert(it, "amazing");

	REQUIRE(list.GetSize() == 3);

	it = list.Begin();
	REQUIRE(*it++ == "hello");
	REQUIRE(*it++ == "amazing");
	REQUIRE(*it == "world");
}

TEST_CASE("CStringList Erase", "[CStringList]") {
	CStringList list;
	list.PushBack("hello");
	list.PushBack("amazing");
	list.PushBack("world");

	auto it = list.Begin();
	++it;
	list.Erase(it);

	REQUIRE(list.GetSize() == 2);

	it = list.Begin();
	REQUIRE(*it++ == "hello");
	REQUIRE(*it == "world");
}