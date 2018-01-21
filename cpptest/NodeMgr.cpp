
#include "NodeMgr.h"
#include <list>

void NodeMgr::AddDependGroup(const std::string& serviceName, const std::vector<std::string>& depend)
{
	if (m_service.end() == m_service.find(serviceName))
		m_service[serviceName] = std::shared_ptr<Node>(new Node(serviceName));

	for (auto& it : depend)
	{
		if (m_service.end() == m_service.find(it))
			m_service[it] = std::shared_ptr<Node>(new Node(it));

		auto serviceNode = m_service[serviceName];
		auto dependNode = m_service[it];
		serviceNode->AddDepend(dependNode);
		dependNode->AddNext(serviceNode);
	}
}

std::string NodeMgr::MakeServiceOrder(const std::vector<std::list<std::shared_ptr<Node>>>& serviceOrder)
{
	std::string output;
	for (auto& it : serviceOrder)
	{
		output += "(";
		for (auto& iter : it)
		{
			output += iter->GetName();
			output += ",";
		}
		output = output.substr(0, output.size() - 1);
		output += ")->";
	}
	output = output.substr(0, output.size()-2);

	return output;
}

std::tuple<ErrCode, std::string> NodeMgr::Calc()
{
	std::vector<std::list<std::shared_ptr<Node>>> serviceOrder;
	std::list<std::shared_ptr<Node>> listNode;

	while (m_service.size() > 0)
	{
		for (auto it = m_service.begin(); it != m_service.end(); ++it)
		{
			if (0 == it->second->GetVecPreview().size())
				listNode.push_back(it->second);
		}

		if (0 == listNode.size())
		{
			std::string circle = DetectCircle();
			return std::make_tuple(ErrCode::eCircle, circle);
		}
		else
		{
			for (auto iter = listNode.begin(); iter != listNode.end(); ++iter)
			{
				auto next = (*iter)->GetVecNext();
				for (auto sub_iter = next.begin(); sub_iter != next.end();++sub_iter)
				{
					(*sub_iter)->RevokePreview(*iter);
				}
				(*iter)->GetVecNext().clear();
				m_service.erase((*iter)->GetName());
			}
			serviceOrder.push_back(listNode);
			listNode.clear();
		}
	}
	
	std::string output = MakeServiceOrder(serviceOrder);
	return std::make_tuple(ErrCode::eOk, output);
}

std::string NodeMgr::DetectCircle()
{
redo:
	bool bOk = false;
	for (auto it = m_service.begin(); it != m_service.end();)
	{
		auto nextIter = ++it;
		it--;
		if (0 == it->second->GetVecNext().size())
		{
			for (auto iter = it->second->GetVecPreview().begin(); iter != it->second->GetVecPreview().end(); ++iter)
			{
				(*iter)->RevokeNext(it->second);
			}
			m_service.erase(it);
			bOk = true;
		}

		it = nextIter;
	}
	if (bOk)
		goto redo;

	std::string circleOutput;
	auto it = m_service.begin()->second;
	while (1)
	{
		if (!it->IsVisit())
		{
			circleOutput += it->GetName();
			circleOutput += "->";
			it->SetVisit();
			it = it->GetVecNext().front();
		}
		else{
			circleOutput += it->GetName();
			break;
		}
	}
	
	return circleOutput;
}