#pragma once

#include <string>
#include <memory>

class Node
{
public:
	std::string data;
	std::unique_ptr<Node> next;
	Node* prev;

	Node(const std::string& str) : data(str), next(nullptr), prev(nullptr)
	{
	}

	Node(std::string&& str) : data(std::move(str)), next(nullptr), prev(nullptr)
	{
	}
};