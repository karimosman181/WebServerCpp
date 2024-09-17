#pragma once
#include <string>
#include <stdexcept>
#include <iostream>
#include <fstream>


enum class TOKEN
{
    CURLY_OPEN,
    CURLY_CLOSE,
    COLON,
    STRING,
    NUMBER,
    ARRAY_OPEN,
    ARRAY_CLOSE,
    COMMA,
    BOOLEAN,
    NULL_TYPE
};

struct Token
{
    std::string value;
    TOKEN type;
    std::string toString()
    {
        switch (type)
        {
        case TOKEN::CURLY_OPEN:
        {
            return "Curly open";
        }
        case TOKEN::CURLY_CLOSE:
        {
            return "Curly close";
        }
        case TOKEN::COLON:
        {
            return "COLON";
        }
        case TOKEN::NUMBER:
        {
            return "Number: " + value;
        }
        case TOKEN::STRING:
        {
            return "String: " + value;
        }

        case TOKEN::ARRAY_OPEN:
        {
            return "Array open";
        }
        case TOKEN::ARRAY_CLOSE:
        {
            return "Array close";
        }
        case TOKEN::COMMA:
        {
            return "Comma";
        }
        case TOKEN::BOOLEAN:
        {
            return "Boolean: " + value;;
        }

        case TOKEN::NULL_TYPE:
        {
            return "Null";
        }

        }
    }
};


class Tokenizer
{
    std::fstream file;
    size_t prevPos;

public:
    //gets the next character after skipping all the whitespace and newlines.
    auto getWithoutWhiteSpace();

    // getToken, the logic is :
    // For characters like ‘[’, ‘, ’, ‘]’, ‘{ ’, ‘ }’, map it to the corressponding enum type 
    // for string, keep consuming characters till ‘"’ is reached 
    // for numbers, keep consuming characters consecutive number characters.
    // store the string / number in the “value” field of the token.
    auto getToken();

    auto hasMoreTokens();

    // goes back to the previous token. 
    void rollBackToken();
};