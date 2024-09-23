#include "Json.h"


/**
* this contains the private properties of a JSON instance.
*/
struct Json::Impl {
	/**
	* these are the different kinds of values that a JSON object can be.
	* 
	*/

	enum class Type {
		Null,
		Boolean
	};

	/**
	*  This indecates the type of the value represented
	* by the JSON object
	*/
	Type type = Type::Null;

	/**
	* this holds the actual value repesented by the JSON 
	* object. Use the number that matches the type.
	*/
	union {
		bool booleanValue;
	};
	 
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
	impl_->type = Impl::Type::Null;
}

Json::Json(bool value) : impl_(new Impl)
{
	impl_->type = Impl::Type::Boolean;
	impl_->booleanValue = value;
}

std::string Json::toString() const
{
	switch (impl_->type) {
	case Impl::Type::Null: return "null";
	case Impl::Type::Boolean: return impl_->booleanValue ? "true": "false";
	default: return "!!!";
	}
	//return "";
}

Json Json::parse(const std::string& format)
{
	if (format == "null") {
		return nullptr;
	}
	else if (format == "false") {
		return false;
	}
	else if (format == "true") {
		return true;
	}
	else {
		return Json();
	}
}
