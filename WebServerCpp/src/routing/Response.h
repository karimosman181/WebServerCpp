#pragma once
#include <string>
#include "json.h"


struct Response {
	std::string body;
};

// To Do:
// maybe a class that have two functions one to send back a view as in html and other  in json


class Resp
{

public :
	std::string notFound();
	std::string view(std::string path );
	std::string js(std::string path);
	std::string css(std::string path);
	std::string image(std::string path);
	std::string json(Json::Value data);


};