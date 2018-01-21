#include "Node.h"
#include <tuple>
#include <map>
#include <list>

class NodeMgr
{
public:
	NodeMgr()	{}

	~NodeMgr()	{}

	//��ӷ��������飬�������a��������b��c����AddDependGroup("a", std::vector<std::string>{"b", "c"})
	void AddDependGroup(const std::string& serviceName, const std::vector<std::string>& depend);

	//����������˳��std::get<0>Ϊ������
	std::tuple<ErrCode, std::string> Calc();

private:
	//��⻷״
	std::string DetectCircle();

	//��ӡ��������˳��
	std::string MakeServiceOrder(const std::vector<std::list<std::shared_ptr<Node>>>& serviceOrder);

private:
	std::map<std::string, std::shared_ptr<Node>> m_service;
};