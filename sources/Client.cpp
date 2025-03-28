#include "../includes/Client.hpp"

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

void Client::MessageClient(std::string msg)
{
    send(_socket, msg.c_str(), msg.length() + 1, 0);
}

void Client::MessageClient(int nb)
{
    std::ostringstream oss;
    oss << nb;
    std::string msg = oss.str();
    send(_socket, msg.c_str(), msg.length() + 1, 0);
}

bool Client::ValidName(std::string str)
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

void Client::ExecuteCommand(std::string input)
{
    // reset command and arguments
    _cmd.clear();
    _arguments.clear();
    
    // transform input into a legible command
    int command_id = Parser(input);

    // execute command by id
    int return_nb = CommandHandler(command_id);

    // if needed, show user the error
    if (return_nb >= 400)
        PrintErrorMessage(return_nb);
    else if (return_nb > 0)
        PrintSuccessMessage(return_nb);
}

/* setters */
void Client::SetSocket(int s) { _socket = s; }
