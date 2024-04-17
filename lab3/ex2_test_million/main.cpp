#include <iostream>
#include <fstream>

int main()
{
	std::ofstream out("../1.txt");
	out << "let x0 = 1" << std::endl;
	size_t i;
	for (i = 1; i <= 1000000; i++)
	{
		out << "fn x" << i << " = x" << i - 1 << " + x0" << std::endl;
	}
	out << "print x" << i - 1 << std::endl;

	return EXIT_SUCCESS;
}