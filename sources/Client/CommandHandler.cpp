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

    // login commands, QUIT and HELP
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

    case QUIT:
        return quit();
    }

    // authentication check to use other commands
    if (_authenticated_check == false)
        return ERR_NOT_AUTHENTICATED;

    switch (command_id)
    {
    case PING:
        return ping();

    case JOIN:
        return join();

    case PART:
        return part();
    }

    return 0;
}

void Client::printMessage(int message_id)
{
    std::ostringstream oss;

    // if there is no message
    if (message_id == 0)
        return;

    // if its a error
    if (message_id >= 400)
        oss << RED BOLT << message_id << ": ";

    switch (message_id)
    {
        // error messages
        {
        case ERR_NO_SUCH_NICK:
            oss << "No such nick/channel" << RESEND;
            break;
        case ERR_NO_SUCH_CHANNEL:
            oss << "No such channel" << RESEND;
            break;
        case ERR_CANNOT_SEND_TO_CHAN:
            oss << "Cannot send to channel" << RESEND;
            break;
        case ERR_TOO_MANY_CHANNELS:
            oss << "Too many channels" << RESEND;
            break;
        case ERR_UNKNOWN_COMMAND:
            oss << "Unknown command or invalid argument" << RESEND;
            break;
        case ERR_NO_NICKNAME_GIVEN:
            oss << "No nickname given" << RESEND;
            break;
        case ERR_ERRONEUS_NICKNAME:
            oss << "Erroneous nickname" << RESEND;
            break;
        case ERR_NICKNAME_IN_USE:
            oss << "Nickname is already in use" << RESEND;
            break;
        case ERR_USER_NOT_IN_CHANNEL:
            oss << "User is not in the channel" << RESEND;
            break;
        case ERR_NOT_ON_CHANNEL:
            oss << "Not on channel" << RESEND;
            break;
        case ERR_USER_ALREADY_INVITED:
            oss << "User is already invited" << RESEND;
            break;
        case ERR_USER_ON_CHANNEL:
            oss << "User is already on the channel" << RESEND;
            break;
        case ERR_NEED_MORE_PARAMS:
            oss << "Need more parameters" << RESEND;
            break;
        case ERR_ALREADY_REGISTERED:
            oss << "Already registered" << RESEND;
            break;
        case ERR_NOT_AUTHENTICATED:
            oss << "Not authenticated" << RESEND;
            break;
        case ERR_PASSWD_MIS_MATCH:
            oss << "Password mismatch" << RESEND;
            break;
        case ERR_INVALID_PASSWORD:
            oss << "Invalid password" << RESEND;
            break;
        case ERR_CHANNEL_IS_FULL:
            oss << "Channel is full" << RESEND;
            break;
        case ERR_UNKNOWN_MODE:
            oss << "Unknown mode" << RESEND;
            break;
        case ERR_INVITE_ONLY_CHAN:
            oss << "Invite only channel" << RESEND;
            break;
        case ERR_BAD_CHANNEL_KEY:
            oss << "Bad channel key" << RESEND;
            break;
        case ERR_BAD_CHAN_MASK:
            oss << "Bad channel mask" << RESEND;
            break;
        case ERR_CHAN_OP_PRIV_NEEDED:
            oss << "Channel operator privileges needed" << RESEND;
            break;
        case ERR_NO_OPER_HOST:
            oss << "No operator host" << RESEND;
            break;
        case ERR_USERS_DONT_MATCH:
            oss << "Users don't match" << RESEND;
            break;
        case ERR_INVALID_INPUT:
            oss << "Invalid Input" << RESEND;
            break;
        case ERR_EMPTY_INPUT:
            oss << "Empty Input" << RESEND;
            break;
        case ERR_ERRONEUS_USER:
            oss << "Erroneous User" << RESEND;
            break;
        case ERR_ERRONEUS_REAL_NAME:
            oss << "Erroneous Real Name" << RESEND;
            break;
        }

        // other messages
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
            break;
        }

        // debug only messages
        {
        case CHANNEL_CREATED:
            oss << BRIGHT_MAGENTA BOLT << "Channel created: " << WHITE << _arguments[0] << RESEND;
            break;
        case JOINED_CHANNEL:
            oss << BRIGHT_MAGENTA BOLT << "You just joined a channel: " << WHITE << _arguments[0] << RESEND;
            break;
        case CHANNEL_OP:
            oss << BRIGHT_MAGENTA BOLT << "You just became a channel OP: " << WHITE << _arguments[0] << RESEND;
            break;
        case LEAVE_CHANNEL:
            oss << BRIGHT_MAGENTA BOLT << "You left the channel: " << WHITE << _arguments[0] << RESEND;
            break;
        }
    }

    messageClient(oss.str());
}
