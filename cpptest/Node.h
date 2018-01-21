#include <iostream>
#include <vector>
#include <memory>
#include <string>

enum class ErrCode
{
	eOk = 0,
	eCircle = -99,	//检测到环状
	eEmptyService	//没有设置输入
};

class Node : public std::enable_shared_from_this<Node>
{
public:
	Node(const std::string& name) { m_name = name; };

	~Node() {};

	//添加依赖
	bool AddDepend(const std::shared_ptr<Node>);

	//添加后继
	bool AddNext(const std::shared_ptr<Node>);

	//移除依赖
	bool RevokePreview(const std::shared_ptr<Node>);

	//移除后继
	bool RevokeNext(const std::shared_ptr<Node>);

	//该节点设为已访问
	void SetVisit() { m_bVisit = true; };

	//询问节点是否被访问过
	bool IsVisit()	{ return m_bVisit; };

	//获取服务名
	const std::string& GetName()	{ return m_name; }

	//获取所有前向依赖
	std::vector<std::shared_ptr<Node>>& GetVecPreview() { return m_vecPreview; }

	//获取所有后向依赖（后继）
	std::vector<std::shared_ptr<Node>>& GetVecNext()	{ return m_vecNext; }

private:
	std::vector<std::shared_ptr<Node>> m_vecPreview;
	std::vector<std::shared_ptr<Node>> m_vecNext;
	std::string m_name;
	bool m_bVisit = false;
};