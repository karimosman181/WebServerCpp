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
		res->body = resp.image(path);
	}

}


void handleAssets(Request* req, Response* res)
{
	Resp resp;
	std::string type = req->url_params["type"];
	std::string path = req->url_params["path"];

	if (type == "css") {
		res->body = resp.css(path);
	}
	else if (type == "js") {
		res->body = resp.js(path);
	}
	else {
		res->body = resp.notFound();
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
	router.add_route("/assets/:type/:path", "GET", handleAssets);
}
