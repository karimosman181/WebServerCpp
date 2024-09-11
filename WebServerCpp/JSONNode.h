#pragma once
#include <map>
#include <string>
#include <vector>
#include <memory>

namespace JSON {

    using JSONObject = std::map<std::string, std::shared_ptr<JSONNode>>;
    using JSONList = std::vector<std::shared_ptr<JSONNode>>;

    class JSONNode {
        enum class Type { OBJECT, LIST, STRING, NUMBER, BOOLEAN, NULL_TYPE };
        union Values {
            JSONObject* object;
            JSONList* list;
            std::string* s;
            float fValue;
            bool bValue;
        } values;
        Type type;


    public:

    };
}