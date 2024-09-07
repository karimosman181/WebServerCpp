#include "Controller.h"
#include <istream>
#include <fstream>

void handleMainPage(Request* req, Response* res)
{
	fprintf(stdout, "connected\n");
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
	router.add_route("/", "GET", handleMainPage);
	return &router;
}

void Controller::RegisterRoutes() {
	fprintf(stdout, "registering\n");
	/*router.add_route("/", "GET", handleMainPage);*/
}
