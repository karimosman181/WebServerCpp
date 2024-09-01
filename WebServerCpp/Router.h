#pragma once

#include <string>
#include <map>


class Router
{

public:
	typedef int (*FnPtr)(std::string);
	std::map<std::string, FnPtr> routes;



};