#pragma once
#include <string>
#include "json.h"

class Template
{

public:
	std::string sanitizeHtml(const std::string& input);
	std::string processTemplate(const std::string& content, const Json::Value context);

};