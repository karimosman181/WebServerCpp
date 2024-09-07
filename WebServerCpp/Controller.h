#pragma once
#include "router.h"
#include "Request.h"
#include "Response.h"


class Controller
{

private:
	// Create router
	Router router;

public:
	Router* getRouter();

	void RegisterRoutes();
};