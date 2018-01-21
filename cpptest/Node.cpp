#include "Node.h"


bool Node::AddDepend(const std::shared_ptr<Node> other)
{
	if (nullptr == other)
		throw - 1;

	for (auto& it : m_vecPreview)
	{
		if (it->GetName() == other->GetName())
			return true;
	}

	m_vecPreview.push_back(other);
	other->AddNext(shared_from_this());

	return true;
}

bool Node::AddNext(const std::shared_ptr<Node> other)
{
	for (auto& it : m_vecNext)
	{
		if (it->GetName() == other->GetName())
			return true;
	}

	m_vecNext.push_back(other);
	return true;
}

bool Node::RevokePreview(const std::shared_ptr<Node> other)
{
	for (auto it = m_vecPreview.begin(); it != m_vecPreview.end(); it++)
	{
		if (*it == other)
		{
			m_vecPreview.erase(it);
			return true;
		}
	}


	return true;
}

bool Node::RevokeNext(const std::shared_ptr<Node> other)
{
	for (auto it = m_vecNext.begin(); it != m_vecNext.end(); it++)
	{
		if (*it == other)
		{
			m_vecNext.erase(it);
			return true;
		}
	}

	return true;
}