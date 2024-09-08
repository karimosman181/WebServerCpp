#include "Controller.h"
#include <istream>
#include <fstream>

void handleMainPage(Request* req, Response* res)
{
	std::string path = "\\index.html";

	// Open the document in the local file system
	std::ifstream f(".\\www" + path);


	if (f.good())
	{
		std::string str((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
		std::string content = str;
		res->body = content;
	}

};


Router* Controller::getRouter() {
	RegisterRoutes();

	return &router;
}

void Controller::RegisterRoutes() {
	router.add_route("/", "GET", handleMainPage);
}
