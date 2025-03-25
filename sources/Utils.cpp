#include "../includes/Utils.hpp"

std::vector<std::string> Utils::Split(const std::string &str, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;

    for (size_t i = 0; i < str.length(); ++i)
    {
        if (str[i] == delimiter)
        {
            if (!token.empty())
            {
                tokens.push_back(token);
                token.clear();
            }
        }
        else
        {
            token += str[i];
        }
    }

    if (!token.empty())
    {
        tokens.push_back(token);
    }

    return tokens;
}

void Utils::PrintVector(std::vector<std::string> vec)
{
    std::vector<std::string>::iterator it;
    for (it = vec.begin(); it != vec.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
}