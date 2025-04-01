#include "../../includes/Utils.hpp"

std::vector<std::string> Utils::split(const std::string &str, char delimiter)
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

void Utils::printVector(std::vector<std::string> vec)
{
    std::vector<std::string>::iterator it;
    for (it = vec.begin(); it != vec.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
}

/*
 *
 * if str1 == str2
 * return TRUE
 *
 * if str1 != str2
 * return FALSE
 *
 */
bool Utils::compareStringsCaseInsensitive(std::string str1, std::string str2)
{
    if (str1.length() != str2.length())
        return false;
    for (size_t i = 0; i < str1.length(); ++i)
    {
        if (std::toupper(str1[i]) != std::toupper(str2[i]))
            return false;
    }
    return true;
}
