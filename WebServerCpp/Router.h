#pragma once

#include <string>
#include <map>
#include <vector>
#include "response.h"
#include "request.h"


class Router
{
	struct Route {
		std::string url_regex;
		std::string request_method;
		void (*callback)(Request*, Response*);
	};

	std::vector<Route> routes;
	

public:
	//add route to router
	void add_route(std::string url_regex,
		std::string request_method,
		void (*callback)(Request*, Response*));


};