#include "Controller.h"
#include <istream>
#include <fstream>
#include "JSONNode.h"

void handleMainPage(Request* req, Response* res)
{
	Resp resp;

	std::string path = "\\index.html";
	res->body = resp.view(path);
};

void handleJSON(Request* req, Response* res)
{
	Resp resp;
	
	JSON json = JSON(JSONType::OBJECT);
	json["name"] = "test";
	json["age"] = 24;
	json["height"] = 5.11;
	json["hobbies"] = std::vector<JSON>{ "Gym" };
	json["valid"] = true;
	json["school"] = JSON(JSONType::OBJECT);
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
