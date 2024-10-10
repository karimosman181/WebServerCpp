#pragma once
#include "BaseController.h"

class HomeController : public BaseController {
public:
    void RegisterRoutes(Router* router) override {
        router->add_route("/", "GET", handleMainPage);
        router->add_route("/json", "GET", handleJSON);
        router->add_route("/json", "POST", handleJSONReq);
    }

    static void handleMainPage(Request* req, Response* res);
    static void handleJSON(Request* req, Response* res);
    static void handleJSONReq(Request* req, Response* res);
};
