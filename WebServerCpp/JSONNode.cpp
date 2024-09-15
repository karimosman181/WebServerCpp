#include "JSONNode.h"
#include <stdexcept>

auto JSON::JSONNode::returnObject() {
    if (type == Type::OBJECT) {
        return *values.object;
    }
    throw std::logic_error("Improper return");
}

auto JSON::JSONNode::returnFloat() {
    if (type == Type::NUMBER) {
        return values.fValue;
    }
    throw std::logic_error("Improper return");
}

auto JSON::JSONNode::returnList() {
    if (type == Type::LIST) {
        return *values.list;
    }
    throw std::logic_error("Improper return");
}

auto JSON::JSONNode::returnString() {
    if (type == Type::STRING) {
        return *values.s;
    }
    throw std::logic_error("Improper return");
}


void JSON::JSONNode::setObject(JSONObject* object) 
{
    this->values.object = object;
    type = Type::OBJECT;
}

void JSON::JSONNode::setString(std::string* s)
{
    this->values.s = s;
    type = Type::STRING;
}

void JSON::JSONNode::setNumber(float f)
{
    this->values.fValue = f;
    type = Type::NUMBER;
}

void JSON::JSONNode::setList(JSONList* list)
{
    this->values.list = list;
    type = Type::LIST;
}

void JSON::JSONNode::setBoolean(bool v)
{
    this->values.bValue = v;
    type = Type::BOOLEAN;
}

void JSON::JSONNode::setNull()
{
    type = Type::NULL_TYPE;
}