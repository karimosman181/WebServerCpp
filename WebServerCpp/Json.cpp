#include "Json.h"


/**
* this contains the private properties of a JSON instance.
*/
struct Json::Impl {

};

//Json::~Json() = default;
//Json::Json(const Json&) = default;
//Json::Json(Json&&) = default;
//Json& Json::operator = (const Json&) = default;
//Json& Json::operator = (Json&&) = default;


Json::Json() : impl_(new Impl) 
{
}

Json::Json(nullptr_t) : impl_(new Impl)
{
}

std::string Json::toString() const
{
	return "";
}

Json Json::parse(const std::string& format)
{
	 return Json();
}
