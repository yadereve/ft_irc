#include "../../includes/Client.hpp"

int Client::parser(std::string raw_input)
{
    // remove input las char '\n'
    std::string input = raw_input.substr(0, raw_input.find_first_of("\n"));

    // handle void input
    if (input.length() <= 0)
        return ERR_EMPTY_INPUT;

    // set message and cmd
    _arguments = Utils::split(input, ' ');
    _cmd = _arguments[0];

    // get command id
    std::vector<std::string> command_list;
    command_list = _server.getCommandList();
    int command_id = -1;
    for (size_t i = 0; i < command_list.size(); i++)
    {
        if (Utils::compareStringsCaseInsensitive(_cmd, command_list[i]) == true)
        {
            _arguments.erase(_arguments.begin());
            command_id = i + 1;
            break;
        }
    }

    // handle non existent command
    if (command_id == -1)
        return ERR_INVALID_INPUT;

    return command_id;
}

int Client::commandHandler(int command_id)
{
    // if command_id hasn't a command, it is a error, so return it
    if (command_id > (int)_server.getCommandList().size())
        return command_id;

    // execute commands
    switch (command_id)
    {

    // login commands
    case PASS:
        return pass();

    case NICK:
        return nick();

    case USER:
        return user();

    // general commands
    case HELP:
        return help();

    case QUIT:
        return quit();
    
    case PING:
        return ping();

    // channel commands
    case JOIN:
        return join();

    case PART:
        return part();

    case TOPIC:
        return topic();

    case KICK:
        return kick();

    case PRIVMSG:
        return privmsg();

    case INVITE:
        return invite();
    }

    return 0;
}


