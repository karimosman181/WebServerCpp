#include "AssetsController.h"
#include <istream>
#include <fstream>

void AssetsController::handleAssets(Request* req, Response* res) {
	Resp resp;
	std::string type = req->url_params["type"];
	std::string path = req->url_params["path"];


    // Set MIME type based on file type
    if (type == "css") {
        res->body = resp.css(path);
    }
    else if (type == "js") {
        res->body = resp.js(path);
    }
    else if (type == "img") {
        res->body = resp.image(path);
    }
    else {
        res->body = resp.notFound();
    }
}