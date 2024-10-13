#include "HomeController.h"
#include "json.h"

void HomeController::handleMainPage(Request* req, Response* res)
{
	Resp resp;

	Json::Value json;
	json["name"] = "test";
	json["age"] = 24;
	int myNumbers[5] = { 10, 20, 30, 40, 50 };
	json["arr"] = myNumbers;
	json["bool"] = true;

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
