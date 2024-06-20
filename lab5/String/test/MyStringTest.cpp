#include "catch2/catch_test_macros.hpp"
#include "MyString.h"

TEST_CASE("Null construct")
{
	const char* data = "";
	MyString string;

	REQUIRE(std::equal(data, data + std::strlen(data), string.GetStringData()));
	REQUIRE(string.GetLength() == 0);
	REQUIRE(string.GetCapacity() == 0);
}

TEST_CASE("Construct string with char*")
{
	const char* data = "meow";
	MyString string(data);
	REQUIRE(std::equal(data, data + std::strlen(data), string.GetStringData()));
	REQUIRE(string.GetLength() == 4);
	REQUIRE(string.GetCapacity() == 9);
}

TEST_CASE("Construct string with char* and length")
{
	const char* data = "meow";
	MyString string(data, std::strlen(data) - 1);
	REQUIRE(std::equal(data, data + std::strlen(data) - 1, string.GetStringData()));
	REQUIRE(string.GetLength() == 3);
	REQUIRE(string.GetCapacity() == 7);
}

TEST_CASE("Construct copy string")
{
	MyString string1 = "meow";
	MyString string2(string1);
	REQUIRE(string1 == string2);

	string1 = "meowmeow";
	string1 = string2;
}

TEST_CASE("Construct with move")
{
	MyString string1 = "meow";
	MyString string2(std::move(string1));
	REQUIRE(string2 == "meow");

	MyString string3 = string2;
	REQUIRE(string3 == "meow");
	REQUIRE(string2 == "meow");

	string3 = std::move(string2);
	REQUIRE(string3 == "meow");
	REQUIRE(string2 == "");
	REQUIRE(string2.GetCapacity() == 0);
	REQUIRE(string2.GetLength() == 0);
}

TEST_CASE("Clear string")
{
	MyString string = "meow";
	string.Clear();
	REQUIRE(string == "");
	REQUIRE(string.GetLength() == 0);
}

TEST_CASE("Construct with stl string")
{
	std::string string1 = "deskTOP";
	MyString string2(string1);
	REQUIRE(string2 == "deskTOP");
	REQUIRE(string2 == string1);
}

TEST_CASE("Null symbol")
{
	MyString string = "hel\0lo";
	REQUIRE(string == "hel\0lo");
}

TEST_CASE("SubString")
{
	MyString string = "meow";
	REQUIRE(string.SubString(2, 2) == "ow");
	REQUIRE(string.SubString(2, 3) == "ow");
	REQUIRE(string.SubString(0, 4) == "meow");
}

TEST_CASE("Sum")
{
	MyString string1 = "meow";
	std::string stlString = "meow2";
	const char* string3 = "56";

	MyString string2 = string1 + '1';
	REQUIRE(string2 == "meow1");
	string2 = string1 + stlString;
	REQUIRE(string2 == "meowmeow2");
	string2 = string1 + string2;
	REQUIRE(string2 == "meowmeowmeow2");
	string2 = string1 + string3;
	REQUIRE(string2 == "meow56");
}

TEST_CASE("Concatenate")
{
	MyString string1 = "Hello ";
	MyString string2 = "World";
	string1 += string2;
	REQUIRE(string1 == "Hello World");
	REQUIRE(string1 != "Hello ");
	string1 = "me";
	string1 += string2;
	REQUIRE(string1 == "meWorld");
	string1 = "";
	string1 += "Hello";
	REQUIRE(string1 == "Hello");
}

TEST_CASE("Cmp")
{
	MyString str1 = "apple";
	MyString str2 = "banana";
	MyString str3 = str1;

	REQUIRE(!(str1 == str2));
	REQUIRE(str1 != str2);
	REQUIRE(str1 == str3);
	REQUIRE(str1 < str2);
	REQUIRE(str2 > str1);
	REQUIRE(str1 <= str3);
	REQUIRE(str2 >= str1);
}

TEST_CASE("Index")
{
	const MyString constString = "meow";
	REQUIRE_THROWS(constString[4]);

	REQUIRE(constString[3] == 'w');

	MyString string = "meow";
	REQUIRE(string[3] == 'w');
	string[3] = 'u';
	REQUIRE(string == "meou");
}