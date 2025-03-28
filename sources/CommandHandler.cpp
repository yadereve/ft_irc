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

int Client::Parser(std::string raw_input)
{
    // remove input las char '\n'
    std::string input = raw_input.substr(0, raw_input.find_first_of("\n"));

    // handle void input
    if (input.length() <= 0)
        return ERR_EMPTY_INPUT;

    // set message and cmd
    _arguments = Utils::Split(input, ' ');
    _cmd = _arguments[0];

    // get command id
    std::vector<std::string> command_list;
    CommandListInitializer(command_list);
    int command_id = -1;
    for (size_t i = 0; i < command_list.size(); i++)
    {
        if (_cmd == command_list[i])
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

int Client::CommandHandler(int command_id)
{
    // login and HELP commands
    switch (command_id)
    {
    case PASS:
        return Pass();
    case NICK:
        return Nick();
    case USER:
        return User();
    case HELP:
        return Help();
    }

    // authentication check to use other commands
    if (_authenticated_check == false)
        return ERR_NOT_AUTHENTICATED;

    switch (command_id)
    {
    case OPER:
        return Oper();
    case PING:
        return Ping();
    case QUIT:
        return Quit();
    }

    // if command_id hasn't a command, it is a error, so return it
    return command_id;
}

void Client::PrintErrorMessage(int nb)
{
    std::ostringstream oss;

    oss << RED BOLT << nb << ": ";

    switch (nb)
    {
    case ERR_NO_SUCH_NICK:
        oss << "No such nick/channel";
        break;
    case ERR_NO_SUCH_CHANNEL:
        oss << "No such channel";
        break;
    case ERR_CANNOT_SEND_TO_CHAN:
        oss << "Cannot send to channel";
        break;
    case ERR_TOO_MANY_CHANNELS:
        oss << "Too many channels";
        break;
    case ERR_UNKNOWN_COMMAND:
        oss << "Unknown command or invalid argument";
        break;
    case ERR_NO_NICKNAME_GIVEN:
        oss << "No nickname given";
        break;
    case ERR_ERRONEUS_NICKNAME:
        oss << "Erroneous nickname";
        break;
    case ERR_NICKNAME_IN_USE:
        oss << "Nickname is already in use";
        break;
    case ERR_USER_NOT_IN_CHANNEL:
        oss << "User is not in the channel";
        break;
    case ERR_NOT_ON_CHANNEL:
        oss << "Not on channel";
        break;
    case ERR_USER_ALREADY_INVITED:
        oss << "User is already invited";
        break;
    case ERR_USER_ON_CHANNEL:
        oss << "User is already on the channel";
        break;
    case ERR_NEED_MORE_PARAMS:
        oss << "Need more parameters";
        break;
    case ERR_ALREADY_REGISTERED:
        oss << "Already registered";
        break;
    case ERR_NOT_AUTHENTICATED:
        oss << "Not authenticated";
        break;
    case ERR_PASSWD_MIS_MATCH:
        oss << "Password mismatch";
        break;
    case ERR_INVALID_PASSWORD:
        oss << "Invalid password";
        break;
    case ERR_CHANNEL_IS_FULL:
        oss << "Channel is full";
        break;
    case ERR_UNKNOWN_MODE:
        oss << "Unknown mode";
        break;
    case ERR_INVITE_ONLY_CHAN:
        oss << "Invite only channel";
        break;
    case ERR_BAD_CHANNEL_KEY:
        oss << "Bad channel key";
        break;
    case ERR_BAD_CHAN_MASK:
        oss << "Bad channel mask";
        break;
    case ERR_CHAN_OP_PRIV_NEEDED:
        oss << "Channel operator privileges needed";
        break;
    case ERR_NO_OPER_HOST:
        oss << "No operator host";
        break;
    case ERR_USERS_DONT_MATCH:
        oss << "Users don't match";
        break;
    case ERR_INVALID_INPUT:
        oss << "Invalid Input";
        break;
    case ERR_EMPTY_INPUT:
        oss << "Empty Input";
        break;
    case ERR_ERRONEUS_USER:
        oss << "Erroneous User";
        break;
    case ERR_ERRONEUS_REAL_NAME:
        oss << "Erroneous Real Name";
        break;
    }

    oss << RESET << std::endl;
    
    MessageClient(oss.str());
}

void Client::PrintSuccessMessage(int nb)
{
    std::ostringstream oss;

    switch (nb)
    {
    case PASSWORD_SUCCESS:
        oss << GREEN << "001: Correct Password" << ITALICS << RESEND;
        break;
    case NICKNAME_SUCCESS:
        oss << GREEN << "001: Nickname assigned: " << _nick << RESEND;
        break;
    case USERNAME_SUCCESS:
        oss << GREEN << "001: Username assigned: " << RESET ITALICS << _user << RESEND;
        oss << GREEN << "001: Real name assigned: " << RESET ITALICS << _real_name << RESEND;
        oss << BRIGHT_BLUE << "001: Welcome to the Internet Relay Chat Network, " << RESET ITALICS << _nick << RESEND;
        break;
    }
    
    MessageClient(oss.str());
}