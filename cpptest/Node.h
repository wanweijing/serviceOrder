#include <iostream>
#include <vector>
#include <memory>
#include <string>

enum class ErrCode
{
	eOk = 0,
	eCircle = -99,	//��⵽��״
	eEmptyService	//û����������
};

class Node : public std::enable_shared_from_this<Node>
{
public:
	Node(const std::string& name) { m_name = name; };

	~Node() {};

	//�������
	bool AddDepend(const std::shared_ptr<Node>);

	//��Ӻ��
	bool AddNext(const std::shared_ptr<Node>);

	//�Ƴ�����
	bool RevokePreview(const std::shared_ptr<Node>);

	//�Ƴ����
	bool RevokeNext(const std::shared_ptr<Node>);

	//�ýڵ���Ϊ�ѷ���
	void SetVisit() { m_bVisit = true; };

	//ѯ�ʽڵ��Ƿ񱻷��ʹ�
	bool IsVisit()	{ return m_bVisit; };

	//��ȡ������
	const std::string& GetName()	{ return m_name; }

	//��ȡ����ǰ������
	std::vector<std::shared_ptr<Node>>& GetVecPreview() { return m_vecPreview; }

	//��ȡ���к�����������̣�
	std::vector<std::shared_ptr<Node>>& GetVecNext()	{ return m_vecNext; }

private:
	std::vector<std::shared_ptr<Node>> m_vecPreview;
	std::vector<std::shared_ptr<Node>> m_vecNext;
	std::string m_name;
	bool m_bVisit = false;
};