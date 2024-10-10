#pragma once
#include "BaseController.h"

class AssetsController : public BaseController {
public:
    void RegisterRoutes(Router* router) override {
        router->add_route("/assets/:type/:path", "GET", handleAssets);  // Use regex to capture full path after type
    }

    static void handleAssets(Request* req, Response* res);
};

