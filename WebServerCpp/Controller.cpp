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


void handleJSONReq(Request* req, Response* res)
{
	Resp resp;

	req->body["params"] = req->params;

	res->body = resp.json(req->body);
}

void handleImages(Request* req, Response* res)
{
	Resp resp;

	std::string path = req->params.get("path", "").asString();

	if (path == "")
		res->body = resp.notFound();
	else {
		fprintf(stdout, "running");
		res->body = resp.image(path);
	}

}


Router* Controller::getRouter() {
	RegisterRoutes();

	return &router;
}

void Controller::RegisterRoutes() {
	router.add_route("/", "GET", handleMainPage);
	router.add_route("/json", "GET", handleJSON);
	router.add_route("/json", "POST", handleJSONReq);
	router.add_route("/img", "GET", handleImages);
}
