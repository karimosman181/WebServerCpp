#include "Template.h"
#include <regex>
#include <algorithm>
#include <cctype>
#include <iostream>

// Function to sanitize HTML input by escaping special characters
std::string Template::sanitizeHtml(const std::string& input) {
    std::string sanitized = input;
    std::map<std::string, std::string> escapeChars = {
        {"&", "&amp;"},
        {"<", "&lt;"},
        {">", "&gt;"},
        {"\"", "&quot;"},
        {"'", "&#x27;"},
        {"/", "&#x2F;"}
    };

    for (const auto& pair : escapeChars) {
        std::string::size_type pos = 0;
        while ((pos = sanitized.find(pair.first, pos)) != std::string::npos) {
            sanitized.replace(pos, pair.first.length(), pair.second);
            pos += pair.second.length();
        }
    }

    return sanitized;
}

// TODO: 
// 1. change the condition from only accepting boolean to running conditions operators (>,<,=);
// 2. 
std::string Template::processTemplate(const std::string& content, const Json::Value context) {
    std::string result = content;

    //result.erase(std::remove_if(result.begin(), result.end(), ::isspace), result.end());

    // Process if-else statements (example: {{#if condition}}...{{#else}}...{{/if}})
    std::regex if_else_regex(R"(\{\{\#if (.*?)\}\}(.*?)\{\{\#else\}\}(.*?)\{\{\/if\}\})", std::regex_constants::ECMAScript | std::regex_constants::nosubs);
    std::sregex_iterator it(result.begin(), result.end(), if_else_regex);
    std::sregex_iterator end;
    std::string tmp1 = result;
    while (it != end) {
        std::smatch match = *it;
        std::string condition = match[1].str();
        std::string trueBlock = match[2].str();
        std::string falseBlock = match[3].str();
    
        // Determine the value of the condition in the context and choose the appropriate block
        std::string replacement;
        if (context[condition] && context[condition].isBool() &&  context.get(condition, false).asBool()) {
            replacement = trueBlock;
        }
        else {
            replacement = falseBlock;
        }

        // Replace the matched if-else block in the result
        std::string matched_string = match.str();
        tmp1.replace(tmp1.find(matched_string), matched_string.length(), replacement);

        ++it; // Move to the next match
    }
    result = tmp1;

    // Process conditional statements (example: {{#if condition}}...{{/if}})
    // Implicit else is an empty string when condition is false
    std::regex if_regex(R"(\{\{\#if (.*?)\}\}(.*?)\{\{\/if\}\})", std::regex_constants::ECMAScript | std::regex_constants::nosubs);
    std::sregex_iterator it_if(result.begin(), result.end(), if_regex);

    std::string tmp2 = result;

    while (it_if != end) {
        std::smatch match = *it_if;
        std::string condition = match[1].str();
        std::string trueBlock = match[2].str();
        
        // If the condition is true, use trueBlock; otherwise, replace with an empty string
        std::string replacement;
        if (context[condition] && context[condition].isBool() && context.get(condition, false).asBool()) {
            replacement = trueBlock;
        }
        else {
            replacement = "";  // Implicit empty else
        }

        // Replace the matched if block in the result
        std::string matched_string = match.str();
        tmp2.replace(tmp2.find(matched_string), matched_string.length(), replacement);

        ++it_if; // Move to the next match
    }
    result = tmp2;

    // Process loops (example: {{#each items}}...{{/each}} as a similar structure to if-else)
    std::regex each_regex(R"(\{\{\#each (.*?)\}\}(.*?)\{\{\/each\}\})", std::regex_constants::ECMAScript | std::regex_constants::nosubs);
    std::sregex_iterator it_each(result.begin(), result.end(), each_regex);

    std::string tmp3 = result;

    while (it_each != end) {
        std::smatch match = *it_each;
        std::string itemKey = match[1].str();
        std::string innerContent = match[2].str();
        
        // If the key exists and is an array, loop over the items; else, render nothing
        std::string loopResult;
        if (context[itemKey] && context[itemKey].isArray()) {
            for (const auto& item : context[itemKey]) {
                std::string tempContent = innerContent;
                std::regex item_regex(R"(\{\{this\}\})");
                tempContent = std::regex_replace(tempContent, item_regex, sanitizeHtml(item.asString())); // Sanitize the item
                loopResult += tempContent;
            }
        }

        // Replace the matched each block in the result
        std::string matched_string = match.str();
        tmp3.replace(tmp3.find(matched_string), matched_string.length(), loopResult);

        ++it_each; // Move to the next match
    }
    result = tmp3;

    //// Templating logic for variable substitution
    std::regex placeholder_regex(R"(\{\{(.*?)\}\})");
    std::sregex_iterator it_var(result.begin(), result.end(), placeholder_regex);
    std::sregex_iterator end_var;

    std::string tmp4 = result;

    while (it_var != end_var) {
        std::smatch match = *it_var;
        std::string key = match[1].str();
        
        // Check if the variable exists in the context (if), else render an empty string
        std::string replacement;
        if (context[key]) {
           replacement = sanitizeHtml(context[key].asString());  // Sanitize and return the value
        }
        else {
            replacement = "";  // Return an empty string if the variable is not found
        }

        ////// Replace the matched variable in the result
        std::string matched_string = match.str();

        tmp4.replace(tmp4.find(matched_string), matched_string.length(), replacement);

        ++it_var; // Move to the next match
    }

    result = tmp4;

    return result;
}