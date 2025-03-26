#include "../includes/Client.hpp"

void CommandListInitializer(std::vector<std::string> &list)
{
    list.push_back("CAP");
    list.push_back("HELP");
    list.push_back("OPER");
    list.push_back("PING");
    list.push_back("QUIT");
    list.push_back("PASS");
    list.push_back("NICK");
    list.push_back("USER");
    list.push_back("WHOIS");
    list.push_back("JOIN");
    list.push_back("MODE");
    list.push_back("TOPIC");
    list.push_back("PART");
    list.push_back("PRIVMSG");
    list.push_back("INVITE");
    list.push_back("KICK");
}

void Client::Parser(std::string raw_input)
{
    // remove input las char '\n'
    std::string input = raw_input.substr(0, raw_input.find_first_of("\n"));

    // handle void input
    if (input.length() <= 0)
        return;

    // set message and cmd
    _message = Utils::Split(input, ' ');
    _cmd = _message[0];

    // get command id
    std::vector<std::string> command_list;
    CommandListInitializer(command_list);
    int command_id = -1;
    for (size_t i = 0; i < command_list.size(); i++)
    {
        if (_cmd == command_list[i])
        {
            _message.erase(_message.begin());
            command_id = i + 1;
            break;
        }
    }

    // handle non existent command
    if (command_id == -1)
    {
        MessageUser(RED "Invalid command\n" RESET);
        return; // error
    }

    CommandHandler(command_id);
}

void Client::CommandHandler(int command_id)
{
    int return_nb = OK;

    switch (command_id)
    {
    case PASS:
        return_nb = Pass();
        break;

    case NICK:
        return_nb = Nick();
        break;
    }

    if (return_nb != 0)
    {
        MessageUser(return_nb);
        MessageUser(RED " - Something was wrong\n" RESET);
    }
    // FeedbackClient(return_nb);
}