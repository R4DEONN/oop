#include <iostream>
#include "string"
#include "set"

struct Student
{
	std::string firstName;
	std::string lastName;
};

struct StudentComparator
{
bool operator()(const Student& student1, const Student& student2) const
{
	if (student1.firstName < student2.firstName)
	{
		return true;
	}
	else if (student1.firstName > student2.firstName)
	{
		return false;
	}

	if (student1.lastName < student2.lastName)
	{
		return true;
	}

	return false;
}

};

int main()
{
	std::set<Student, StudentComparator> studentSet{};

	studentSet.emplace("Kirill", "Borisov");
	studentSet.emplace("Kirill", "Veresnikov");
	studentSet.emplace("Andrey", "Dudin");

	for (const auto& student : studentSet)
	{
		std::cout << student.firstName << " " << student.lastName << std::endl;
	}

	std::cout << std::endl;

	if (auto it = studentSet.find({"Kirill", "Borisov"}); it != studentSet.end())
	{
		std::cout << it->firstName << " " << it->lastName << std::endl;
	}

	for (auto it = studentSet.begin(); it != studentSet.end();)
	{
		if (it->firstName == "Kirill")
		{
			it = studentSet.erase(it);
		}
		else
		{
			++it;
		}
	}

	std::cout << std::endl;

	for (const auto& student : studentSet)
	{
		std::cout << student.firstName << " " << student.lastName << std::endl;
	}


	return EXIT_SUCCESS;
}