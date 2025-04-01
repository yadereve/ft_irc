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
    // login and HELP commands
    switch (command_id)
    {
    case PASS:
        return pass();
    case NICK:
        return nick();
    case USER:
        return user();
    case HELP:
        return help();
    }

    // authentication check to use other commands
    if (_authenticated_check == false)
        return ERR_NOT_AUTHENTICATED;

    switch (command_id)
    {
    case OPER:
        return oper();
    case PING:
        return ping();
    case QUIT:
        return quit();
    }

    // if command_id hasn't a command, it is a error, so return it
    return command_id;
}

void Client::printErrorMessage(int nb)
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

    messageClient(oss.str());
}

void Client::printSuccessMessage(int nb)
{
    std::ostringstream oss;

    switch (nb)
    {
    case PASSWORD_SUCCESS:
        oss << GREEN << "001: Correct Password" << RESEND;
        break;
    case NICKNAME_SUCCESS:
        oss << GREEN << "001: Nickname assigned: " << _nick << RESEND;
        break;
    case USERNAME_SUCCESS:
        oss << GREEN << "001: Username assigned: " << WHITE ITALICS << _user << RESEND;
        oss << GREEN << "001: Real name assigned: " << WHITE ITALICS << _real_name << RESEND;
        oss << BRIGHT_BLUE << "001: Welcome to the Internet Relay Chat Network, " << WHITE ITALICS << _nick << RESEND;
        break;
    case PONG:
        oss << GREEN BOLT << "Pong: " << WHITE << _arguments[0] << RESEND;
    }

    messageClient(oss.str());
}