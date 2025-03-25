#include "../includes/Client.hpp"
#include "../includes/Utils.hpp"

Client::Client(Server &server, int s) : _server(server), _socket(s)
{
    _pass_check = false;
    _nick_check = false;
    _user_check = false;
}

Client::~Client()
{
}

void Client::PrintMessage(std::string msg)
{
    send(_socket, msg.c_str(), msg.length() + 1, 0);
}

void Client::Parser(std::string input)
{
    // error handling
    std::string input2 = input.substr(0, input.find_first_of("\n"));
    if (input2.length() <= 0)
    {
        return;
    }

    // define command list
    std::string command_list[] = {"PASS", "NICK", "USER", "HELP"};
    void (Client::*actions[])() = {
        &Client::Pass,
        &Client::Nick,
        &Client::User,
        &Client::Help};

    // compare input with command list
    _message = Utils::Split(input2, ' ');
    _cmd = _message[0];
    for (size_t i = 0; i < command_list->size(); ++i)
    {
        if (_cmd == command_list[i])
        {
            _message.erase(_message.begin());
            (this->*actions[i])();
            return;
        }
    }
    PrintMessage(RED "Invalid command\n" RESET);
}

/* setters */
void Client::SetSocket(int s) { _socket = s; }
