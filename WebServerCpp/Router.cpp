#include "Router.h"
#include "Request.h"
#include "Response.h"
#include <regex>
#include <string>

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
	fprintf(stdout, std::to_string(routes.size()).c_str());
}

void Router::route_handler(Request* req, Response* res) {
	//ToDo:
	// loop over the registered routes and match with correct url_regex
	// if route found with correct method call callback

	for (auto& r : routes) {
		// match request path with route regex
		std::regex pat{ r.url_regex };
		std::smatch match;

		fprintf(stdout, r.url_regex.c_str());

		if (std::regex_match(req->path, match, pat)
			&& (req->method.compare(r.request_method) == 0)) {
			// call callback
			r.callback(req, res);
			// exit for loop
			break;
		}
	}
}
