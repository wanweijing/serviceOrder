#include "NodeMgr.h"
#include <list>
#include <map>
#include <string>

int main()
{
	NodeMgr mgr;
	mgr.AddDependGroup("b", std::vector < std::string > {"a", "d"});
	mgr.AddDependGroup("a", std::vector < std::string > {"b"});
	mgr.AddDependGroup("c", std::vector < std::string > {"b"});

	auto result = mgr.Calc();
	if (ErrCode::eOk == std::get<0>(result))
	{
		std::cout << "calc is success, order is:" <<std::endl<< std::get<1>(result) << std::endl;
	}
	else
	{
		std::cout << "detect cirle :" <<std::endl<< std::get<1>(result) << std::endl;
	}

	
	return 0;
}