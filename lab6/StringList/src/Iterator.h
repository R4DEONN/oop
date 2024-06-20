#pragma once

#include "Node.h"

class Iterator
{
public:
	Node* node;

	explicit Iterator(Node* node) : node(node)
	{
	}

	std::string& operator*() const
	{
		return node->data;
	}

	std::string* operator->() const
	{
		return &node->data;
	}

	Iterator& operator++()
	{
		node = node->next.get();
		return *this;
	}

	Iterator operator++(int)
	{
		Iterator tmp = *this;
		node = node->next.get();
		return tmp;
	}

	Iterator& operator--()
	{
		node = node->prev;
		return *this;
	}

	Iterator operator--(int)
	{
		Iterator tmp = *this;
		node = node->prev;
		return tmp;
	}

	bool operator==(const Iterator& other) const
	{
		return node == other.node;
	}

	bool operator!=(const Iterator& other) const
	{
		return node != other.node;
	}
};
