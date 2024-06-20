#include "StringList.h"

void CStringList::ClearList() noexcept
{
	while (m_head)
	{
		m_head = std::move(m_head->next);
	}
	m_tail = nullptr;
	m_size = 0;
}

CStringList::CStringList(const CStringList& other) : CStringList()
{
	for (Node* current = other.m_head.get(); current != nullptr; current = current->next.get())
	{
		PushBack(current->data);
	}
}

CStringList::CStringList(CStringList&& other) noexcept
	: m_head(std::move(other.m_head)),
	  m_tail(other.m_tail),
	  m_size(other.m_size)
{
	other.m_tail = nullptr;
	other.m_size = 0;
}

CStringList& CStringList::operator=(const CStringList& other)
{
	if (this != &other)
	{
		ClearList();
		for (Node* current = other.m_head.get(); current != nullptr; current = current->next.get())
		{
			PushBack(current->data);
		}
	}
	return *this;
}

CStringList& CStringList::operator=(CStringList&& other) noexcept
{
	if (this != &other)
	{
		ClearList();
		m_head = std::move(other.m_head);
		m_tail = other.m_tail;
		m_size = other.m_size;

		other.m_tail = nullptr;
		other.m_size = 0;
	}
	return *this;
}

CStringList::~CStringList()
{
	ClearList();
}

void CStringList::PushFront(const std::string& str)
{
	auto newNode = std::make_unique<Node>(str);
	if (m_head)
	{
		newNode->next = std::move(m_head);
		newNode->next->prev = newNode.get();
		m_head = std::move(newNode);
	}
	else
	{
		m_head = std::move(newNode);
		m_tail = m_head.get();
	}
	++m_size;
}

void CStringList::PushFront(std::string&& str)
{
	auto newNode = std::make_unique<Node>(std::move(str));
	if (m_head)
	{
		newNode->next = std::move(m_head);
		newNode->next->prev = newNode.get();
		m_head = std::move(newNode);
	}
	else
	{
		m_head = std::move(newNode);
		m_tail = m_head.get();
	}
	++m_size;
}

void CStringList::PushBack(const std::string& str)
{
	auto newNode = std::make_unique<Node>(str);
	newNode->prev = m_tail;
	if (m_tail)
	{
		m_tail->next = std::move(newNode);
		m_tail = m_tail->next.get();
	}
	else
	{
		m_head = std::move(newNode);
		m_tail = m_head.get();
	}
	++m_size;
}

void CStringList::PushBack(std::string&& str)
{
	auto newNode = std::make_unique<Node>(std::move(str));
	newNode->prev = m_tail;
	if (m_tail)
	{
		m_tail->next = std::move(newNode);
		m_tail = m_tail->next.get();
	}
	else
	{
		m_head = std::move(newNode);
		m_tail = m_head.get();
	}
	++m_size;
}

size_t CStringList::GetSize() const noexcept
{
	return m_size;
}

bool CStringList::isEmpty() const noexcept
{
	return m_size == 0;
}