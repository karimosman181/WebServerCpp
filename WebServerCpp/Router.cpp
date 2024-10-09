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
}

void Router::route_handler(Request* req, Response* res) {
	


	for (auto& r : routes) {
		// Convert :param in the route to a regex capture group
		std::string route_pattern = r.url_regex;
		std::regex param_regex{ R"(:([a-zA-Z_][a-zA-Z0-9_]*))" };  // Matches :param in the URL
		route_pattern = std::regex_replace(route_pattern, param_regex, R"(([^/]+))");  // Replace :param with a regex capture group

		std::regex pat{ route_pattern };
		std::smatch match;

		if (std::regex_match(req->path, match, pat)
			&& (req->method.compare(r.request_method) == 0)) {
			// Capture the named parameters
			std::sregex_iterator param_begin(r.url_regex.begin(), r.url_regex.end(), param_regex);
			std::sregex_iterator param_end;

			// Map to store captured parameters
			std::map<std::string, std::string> params;

			// Loop through the parameters found in the route
			int index = 1;  // Match index starts from 1 because match[0] is the entire match
			for (std::sregex_iterator i = param_begin; i != param_end; ++i, ++index) {
				std::string param_name = (*i)[1].str();  // Get the parameter name (without ':')
				std::string param_value = match[index].str();  // Get the corresponding value from the URL
				params[param_name] = param_value;  // Store param name and value in the map
			}

			// Add parameters to the request object (if Request has a map for params)
			req->url_params = params;

			// call callback
			r.callback(req, res);
			// exit for loop
			break;
		}
	}

	if (res->body.size() == 0) {
		Resp resp;
		res->body = resp.notFound();
	}
	
}
