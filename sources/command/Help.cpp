#include "../../includes/Client.hpp"

int Client::Help()
{
    std::ostringstream oss;

    oss << std::endl;
    Pass(oss);
    oss << std::endl;
    Nick(oss);
    oss << std::endl;
    User(oss);
    oss << std::endl;

    MessageClient(oss.str());

    return 0;
}
