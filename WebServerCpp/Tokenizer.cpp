#include "Tokenizer.h"
#include <stdexcept>
#include <iostream>
#include <fstream>

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