#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <iterator>
#include "Node.h"
#include "Iterator.h"
#include "ConstIterator.h"

class CStringList
{
private:
	std::unique_ptr<Node> m_head = nullptr;
	Node* m_tail = nullptr;
	size_t m_size = 0;


public:
	CStringList() = default;

	CStringList(const CStringList& other);

	CStringList(CStringList&& other) noexcept;

	CStringList& operator=(const CStringList& other);

	CStringList& operator=(CStringList&& other) noexcept;

	~CStringList();

	void PushFront(const std::string& str);

	void PushFront(std::string&& str);

	void PushBack(const std::string& str);

	void PushBack(std::string&& str);

	[[nodiscard]] size_t GetSize() const noexcept;

	[[nodiscard]] bool isEmpty() const noexcept;

	void ClearList() noexcept;

	Iterator Begin()
	{
		return Iterator(m_head.get());
	}

	Iterator End()
	{
		return Iterator(m_tail);
	}

	ConstIterator Begin() const
	{
		return ConstIterator(m_head.get());
	}

	ConstIterator End() const
	{
		return ConstIterator(m_tail);
	}

	Iterator Insert(Iterator pos, const std::string& str)
	{
		if (pos.node == nullptr)
		{
			PushBack(str);
			return End();
		}

		auto newNode = std::make_unique<Node>(str);
		newNode->prev = pos.node->prev;
		newNode->next = std::move(pos.node->prev->next);
		pos.node->prev->next = std::move(newNode);
		pos.node->prev = pos.node->prev->next.get();

		++m_size;
		return Iterator(pos.node->prev);
	}

	Iterator Erase(Iterator pos)
	{
		if (pos.node == nullptr)
		{
			return End();
		}

		Node* nextNode = pos.node->next.get();
		if (pos.node->prev)
		{
			pos.node->prev->next = std::move(pos.node->next);
			if (nextNode)
			{
				nextNode->prev = pos.node->prev;
			}
			else
			{
				m_tail = pos.node->prev;
			}
		}
		else
		{
			m_head = std::move(pos.node->next);
			if (m_head)
			{
				m_head->prev = nullptr;
			}
			else
			{
				m_tail = nullptr;
			}
		}

		--m_size;
		return Iterator(nextNode);
	}
};
