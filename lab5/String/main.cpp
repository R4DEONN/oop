#include "iostream"
#include "MyString.h"

int main()
{
	MyString string = "meow";
	MyString string2 = string.SubString(2, 2);
	std::cout << string2.GetStringData() << std::endl;
	return EXIT_SUCCESS;
}