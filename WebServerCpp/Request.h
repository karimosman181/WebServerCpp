#pragma once
#include <iostream>
#include "json.h"

struct Request {
	std::string method;
	std::string path;
	Json::Value body;
	Json::Value params;
	std::map<std::string, std::string> url_params;

	// To do:
	// add body and parameters
	// add a way to parse json
};