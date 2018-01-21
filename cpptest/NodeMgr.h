#include "Node.h"
#include <tuple>
#include <map>
#include <list>

class NodeMgr
{
public:
	NodeMgr()	{}

	~NodeMgr()	{}

	//添加服务依赖组，例如服务a依赖服务b和c，则AddDependGroup("a", std::vector<std::string>{"b", "c"})
	void AddDependGroup(const std::string& serviceName, const std::vector<std::string>& depend);

	//计算服务编排顺序，std::get<0>为错误码
	std::tuple<ErrCode, std::string> Calc();

private:
	//检测环状
	std::string DetectCircle();

	//打印服务启动顺序
	std::string MakeServiceOrder(const std::vector<std::list<std::shared_ptr<Node>>>& serviceOrder);

private:
	std::map<std::string, std::shared_ptr<Node>> m_service;
};