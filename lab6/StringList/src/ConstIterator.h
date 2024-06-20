#pragma once

#include "Node.h"

class ConstIterator
{
public:
	const Node* node;

	explicit ConstIterator(const Node* node) : node(node)
	{
	}

	const std::string& operator*() const
	{
		return node->data;
	}

	const std::string* operator->() const
	{
		return &node->data;
	}

	ConstIterator& operator++()
	{
		node = node->next.get();
		return *this;
	}

	ConstIterator operator++(int)
	{
		ConstIterator tmp = *this;
		node = node->next.get();
		return tmp;
	}

	ConstIterator& operator--()
	{
		node = node->prev;
		return *this;
	}

	ConstIterator operator--(int)
	{
		ConstIterator tmp = *this;
		node = node->prev;
		return tmp;
	}

	bool operator==(const ConstIterator& other) const
	{
		return node == other.node;
	}

	bool operator!=(const ConstIterator& other) const
	{
		return node != other.node;
	}
};
