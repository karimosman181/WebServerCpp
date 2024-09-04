#include "Router.h"
#include <regex>

void Router::add_route(std::string url_regex,
	std::string request_method,
	void (*callback)(Request*, Response*))
{
	// set a Route object to be pushed into the routes vector
	Route route;
	route.url_regex = url_regex;
	route.request_method = request_method;
	route.callback = callback;
	routes.push_back(route);
}

void Router::route_handler(Request* req, Response* res) {
	//ToDo:
	// loop over the registered routes and match with correct url_regex
	// if route found with correct method call callback 
}
