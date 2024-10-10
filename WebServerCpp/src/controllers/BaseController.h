#pragma once
#include "router.h"

class BaseController
{
public:
    virtual void RegisterRoutes(Router* router) = 0;
    virtual ~BaseController() = default;
};
