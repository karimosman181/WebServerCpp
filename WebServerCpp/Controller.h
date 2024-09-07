#pragma once
#include "router.h"


class Controller
{

private:
	// Create router
	Router router;

public:
	Router getRouter();

	void RegisterRoutes();
	
};