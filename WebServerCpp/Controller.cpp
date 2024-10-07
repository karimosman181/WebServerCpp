#include "Controller.h"
#include <istream>
#include <fstream>
#include "json.h"

void handleMainPage(Request* req, Response* res)
{
	Resp resp;

	std::string path = "\\index.html";
	res->body = resp.view(path);
};

void handleJSON(Request* req, Response* res)
{
	Json::Value json;


	Resp resp;
	
	json["name"] = "test";
	json["age"] = 24;
	json["height"] = 5.11;
	json["school"]["name"] = "test school";

	res->body = resp.json(json);
};



Router* Controller::getRouter() {
	RegisterRoutes();

	return &router;
}

void Controller::RegisterRoutes() {
	router.add_route("/", "GET", handleMainPage);
	router.add_route("/json", "GET", handleJSON);
}
