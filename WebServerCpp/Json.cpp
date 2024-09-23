#include "Json.h"
#include "StringExtensions.h"

namespace {
	/**
	* these are the characters that must be escaped in a quoted string in json 
	*/
	const std::set<char> CHARACTERS_TO_ESCAPE_IN_QUOTED_STRING{
		'"', '\\', '\b','\f','\n','\r','\t',
	};
}

/**
* this contains the private properties of a JSON instance.
*/
struct Json::Impl {
	//properties

	/**
	* these are the different kinds of values that a JSON object can be.
	* 
	*/

	enum class Type {
		Null,
		Boolean,
		String
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
		std::string* stringValue;
 	};

	// lifecycle management
	~Impl() {
		switch (type) {
		case Impl::Type::String: {
			delete stringValue;
		}break;
		default: break;
		}
	}

	// Methods

	/**
	* This is the default constructor
	*/
	Impl() = default;
	 
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

Json::Json(std::string& value) : impl_(new Impl)
{
	impl_->type = Impl::Type::String;
	impl_->stringValue = new std::string(value);
}

std::string Json::toString() const
{
	switch (impl_->type) {
	case Impl::Type::Null: return "null";
	case Impl::Type::Boolean: return impl_->booleanValue ? "true": "false";
	case Impl::Type::String: return ("\"" + StringExtensions::Escape(*impl_->stringValue, '\\', CHARACTERS_TO_ESCAPE_IN_QUOTED_STRING) + "\"");
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
	else if (!format.empty() && (format[0] == '"') && (format[format.length() - 1] == '"')) {
		//return StringExtensions::Unescape(format.substr(1,format.length() - 2), '\\');
	}
	else {
		return Json();
	}
}
