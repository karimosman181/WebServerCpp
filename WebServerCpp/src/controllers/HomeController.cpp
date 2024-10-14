#include "HomeController.h"
#include "json.h"

void HomeController::handleMainPage(Request* req, Response* res)
{
	Resp resp;

	Json::Value json;
	json["name"] = "test";
	json["age"] = 24;
	json["bool"] = true;
	json["arr"][0] =  10;
	json["arr"][1] = 20;

	std::string path = "\\index.html";

	res->body = resp.view(path, json);
};

void HomeController::handleJSON(Request* req, Response* res)
{
	Json::Value json;


	Resp resp;

	json["name"] = "test";
	json["age"] = 24;
	json["height"] = 5.11;
	json["school"]["name"] = "test school";

	res->body = resp.json(json);
};


void HomeController::handleJSONReq(Request* req, Response* res)
{
	Resp resp;

	req->body["params"] = req->params;

	res->body = resp.json(req->body);
}
