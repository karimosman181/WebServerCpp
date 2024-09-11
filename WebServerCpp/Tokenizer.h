#pragma once


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

class Tokenizer
{

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