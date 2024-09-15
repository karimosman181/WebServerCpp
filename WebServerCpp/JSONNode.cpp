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