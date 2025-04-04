#include "../../includes/Client.hpp"

Client::Client(Server &server, int s) : _server(server), _socket(s)
{
    _pass_check = false;
    _nick_check = false;
    _user_check = false;
    _authenticated_check = false;
}

Client::~Client()
{
}

/* methods */

void Client::messageClient(std::string msg)
{
    send(_socket, msg.c_str(), msg.length() + 1, 0);
}

void Client::messageClient(int nb)
{
    std::ostringstream oss;
    oss << nb;
    std::string msg = oss.str();
    send(_socket, msg.c_str(), msg.length() + 1, 0);
}

bool Client::validName(std::string str)
{
    // 3 or more chars
    if (str.length() < 3)
        return false;
    // first char is a letter
    if (!isalpha(str[0]))
        return false;
    // only has letters, numbers, '-' and '_'
    for (size_t i = 0; i < str.length(); i++)
        if ((isalnum(str[i]) || str[i] == '-' || str[i] == '_') == false)
            return false;
    return true;
}

bool Client::channelExist(std::string channel_name)
{
    const std::vector<Channel> &channel_list = _server.getChannelList();

    std::vector<Channel>::const_iterator it;
    for (it = channel_list.begin(); it != channel_list.end(); ++it)
    {
        if (it->getName() == channel_name)
            return true;
    }
    return false;
}

void Client::ExecuteCommand(std::string input)
{
    // reset command and arguments
    _cmd.clear();
    _arguments.clear();
    
    // transform input into a legible command
    size_t command_id = parser(input);

    // execute command by id
    int return_message = commandHandler(command_id);

    // print return message
    printMessage(return_message);
}

/* setters */

void Client::SetSocket(int s) { _socket = s; }
