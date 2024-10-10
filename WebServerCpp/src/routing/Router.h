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

	// It will match the path with the registered routes and call the callback to handle the specific request.
	void route_handler(Request* req, Response* res);
};