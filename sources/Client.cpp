#include "../includes/Client.hpp"

Client::Client(Server &server, int s) : _server(server), _socket(s)
{
}

Client::~Client()
{
}

void Client::PrintMessage(std::string msg)
{
    send(_socket, msg.c_str(), msg.length() + 1, 0);
    send(_socket, "\n", 1, 0);
}

void Client::Pass()
{
    std::string str = _server.GetPass();

    PrintMessage(GREEN "Pass ok" RESET);
    PrintMessage(str);
}
void Client::Nick()
{
    PrintMessage(GREEN "Nick ok" RESET);
}
void Client::User()
{
    PrintMessage(GREEN "User ok" RESET);
}

void Client::Parser(std::string input)
{
    // define command list
    std::string command_list[] = {"PASS", "NICK", "USER"};
    void (Client::*actions[])() = {
        &Client::Pass,
        &Client::Nick,
        &Client::User
        };

    // compare input with command list
    _cmd = input.substr(0, input.find("\n"));
    for (int i = 0; i < 3; ++i)
    {
        if (_cmd == command_list[i])
        {
            (this->*actions[i])();
            return;
        }
    }
    PrintMessage(RED "Invalid command" RESET);
}

/* setters */
void Client::SetSocket(int s) { _socket = s; }