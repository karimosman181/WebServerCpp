#include "Tokenizer.h"

auto Tokenizer::getWithoutWhiteSpace()
{
    char c = ' ';
    while ((c == ' ' || c == '\n'))
    {
        file.get(c); // check

        if ((c == ' ' || c == '\n') && !file.good())
        {
            // std::cout << file.eof() << " " << file.fail() << std::endl;
            throw std::logic_error("Ran out of tokens");
        }
        else if (!file.good())
        {
            return c;
        }
    }

    return c;
}

void Tokenizer::rollBackToken()
{
    if (file.eof())
    {
        file.clear();
    }
    file.seekg(prevPos);
}

auto Tokenizer::hasMoreTokens()
{
    return !file.eof();
}

auto Tokenizer::getToken() {
    // string buf;
    char c;
    if (file.eof())
    {
        std::cout << "Exhaused tokens" << std::endl;
        // throw std::exception("Exhausted tokens");
    }
    prevPos = file.tellg();
    c = getWithoutWhiteSpace();

    std::cout << c << std::endl;
    struct Token token;
    if (c == '"')
    {
        token.type = TOKEN::STRING;
        token.value = "";
        file.get(c);
        while (c != '"')
        {
            token.value += c;
            file.get(c);
        }
    }
    else if (c == '{')
    {
        token.type = TOKEN::CURLY_OPEN;
    }
    else if (c == '}')
    {
        token.type = TOKEN::CURLY_CLOSE;
    }
    else if (c == '-' || (c >= '0' && c <= '9'))
    {
        //Check if string is numeric
        token.type = TOKEN::NUMBER;
        token.value = "";
        token.value += c;
        std::streampos prevCharPos = file.tellg();
        while ((c == '-') || (c >= '0' && c <= '9') || c == '.')
        {
            prevCharPos = file.tellg();
            file.get(c);

            if (file.eof())
            {
                break;
            }
            else
            {
                if ((c == '-') || (c >= '0' && c <= '9') || (c == '.'))
                {
                    token.value += c;
                }
                else
                {
                    file.seekg(prevCharPos);
                    // std::cout << c << std::endl;
                }
            }
        }
    }
    else if (c == 'f') {
        token.type = TOKEN::BOOLEAN;
        token.value = "False";
        file.seekg(4, std::ios_base::cur);
    }
    else if (c == 't') {
        token.type = TOKEN::BOOLEAN;
        token.value = "True";
        file.seekg(3, std::ios_base::cur);
    }
    else if (c == 'n') {
        token.type = TOKEN::NULL_TYPE;
        file.seekg(3, std::ios_base::cur);
    }
    else if (c == '[')
    {
        token.type = TOKEN::ARRAY_OPEN;
    }
    else if (c == ']')
    {
        token.type = TOKEN::ARRAY_CLOSE;
    }
    else if (c == ':')
    {
        token.type = TOKEN::COLON;
    }
    else if (c == ',')
    {
        token.type = TOKEN::COMMA;
    }
    return token;
}