#pragma once
#include <iostream>

struct Request {
	std::string method;
	std::string path;

	// To do:
	// add body and parameters
	// add a way to parse json
};