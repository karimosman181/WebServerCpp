#include "Controller.h"
#include <istream>
#include <fstream>

void handleMainPage(Request* req, Response* res)
{
	Resp resp;

	std::string path = "\\index.html";
	res->body = resp.view(path);
};


Router* Controller::getRouter() {
	RegisterRoutes();

	return &router;
}

void Controller::RegisterRoutes() {
	router.add_route("/", "GET", handleMainPage);
}
