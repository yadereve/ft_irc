#include "../includes/Client.hpp"

Client::Client(Server &server, int s) : _server(server), _socket(s)
{
    _pass_check = false;
    _nick_check = false;
    _user_check = false;
}

Client::~Client()
{
}

void Client::MessageUser(std::string msg)
{
    send(_socket, msg.c_str(), msg.length() + 1, 0);
}

void Client::MessageUser(int nb)
{
    std::ostringstream oss;
    oss << nb;
    std::string msg = oss.str();
    send(_socket, msg.c_str(), msg.length() + 1, 0);
}

void Client::ExecuteCommand(std::string input)
{
    // transform input into a legible command
    int command_id = Parser(input);

    // execute command by id
    int error = CommandHandler(command_id);

    // if needed, show user the error
    if (error)
        PrintErrorMessage(error);
}

/* setters */
void Client::SetSocket(int s) { _socket = s; }