#include "../../includes/Client.hpp"

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
            oss << "Bad channel mask, channel name should start with (#)" << RESEND;
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
            break;

        case LOGIN_SUCCESS:
            oss << PINK << std::endl;
            oss << " ┌───────┐                                    " << std::endl;
            oss << " │  001  ├──────────────────────────────────┐ " << std::endl;
            oss << " └───────┘                                  │ " << std::endl;
            oss << "                                            │ " << std::endl;
            oss << " ┌──────────────────────────────────────────┤ " << std::endl;
            oss << " │                                          │ " << std::endl;
            oss << " │   ▗▖ ▗▖▗▄▄▄▖▗▖    ▗▄▄▖ ▗▄▖ ▗▖  ▗▖▗▄▄▄▖   │ " << std::endl;
            oss << " │   ▐▌ ▐▌▐▌   ▐▌   ▐▌   ▐▌ ▐▌▐▛▚▞▜▌▐▌      │ " << std::endl;
            oss << " │   ▐▌ ▐▌▐▛▀▀▘▐▌   ▐▌   ▐▌ ▐▌▐▌  ▐▌▐▛▀▀▘   │ " << std::endl;
            oss << " │   ▐▙█▟▌▐▙▄▄▖▐▙▄▄▖▝▚▄▄▖▝▚▄▞▘▐▌  ▐▌▐▙▄▄▖   │ " << std::endl;
            oss << " │                                          │ " << std::endl;
            oss << " └──────────────────────────────────────────┤ " << std::endl;
            oss << "                                            │ " << std::endl;
            oss << "                                            │ " << std::endl;
            oss << " ┌──────────────────────────────────────────┘ " << std::endl;
            oss << " │                                            " << std::endl;
            oss << " ├───┤ " << _nick << " │" << std::endl;
            oss << " │                                            " << std::endl;
            oss << " ├──────────────────────────────────────────┐ " << std::endl;
            oss << " │    to the Internet Relay Chat Network    │ " << std::endl;
            oss << " └──────────────────────────────────────────┤ " << std::endl;
            oss << "                                            │ " << std::endl;
            oss << "                                            │ " << std::endl;
            oss << " ┌──────────────────────────────────────────┘ " << std::endl;
            oss << " │                                            " << std::endl;
            oss << " │                                            " << std::endl;
            oss << " ├──────────────────────────────────────────┐ " << std::endl;
            oss << " │     Use HELP to see the commands list    │ " << std::endl;
            oss << " └──────────────────────────────────────────┘ " << std::endl;
            oss << RESEND;
            break;

        case PONG:
            oss << GREEN BOLT << "Pong: " << WHITE << _arguments[0] << RESEND;
            break;

        case FIRST_MESSAGE:
            oss << RESEND;
            oss << ORANGE;
            oss << "      ┌─────────────────────────────────────────┐     " << std::endl;
            oss << ORANGE;
            oss << "      │                                         │     " << std::endl;
            oss << ORANGE;
            oss << "      │        ▗▖    ▗▄▖ ▗▄▄▖ ▗▄▄▖▗▖  ▗▖        │     " << std::endl;
            oss << ORANGE;
            oss << "      │        ▐▌   ▐▌ ▐▌▐▌ ▐▌▐▌ ▐▌▝▚▞▘         │     " << std::endl;
            oss << ORANGE;
            oss << "      │        ▐▌   ▐▌ ▐▌▐▛▀▚▖▐▛▀▚▖ ▐▌          │     " << std::endl;
            oss << ORANGE;
            oss << "      │        ▐▙▄▄▖▝▚▄▞▘▐▙▄▞▘▐▙▄▞▘ ▐▌          │     " << std::endl;
            oss << ORANGE;
            oss << "      │                                         │     " << std::endl;
            oss << ORANGE;
            oss << "      └─────────────────────────────────────┬───┘     " << std::endl;
            oss << "                                            │         " << std::endl;
            oss << "         ┌──────────────────────────────────┘         " << std::endl;
            oss << "         │  ┌────────────────────────────┐            " << std::endl;
            oss << "         └──┤  To login use the commands ├──┐         " << std::endl;
            oss << "            └────────────────────────────┘  │         " << std::endl;
            oss << "         ┌──────────────────────────────────┘         " << std::endl;
            oss << "         │     ┌────────┐      ┌──────┐               " << std::endl;
            oss << "         └─────┤ Step 1 ├──────┤ PASS ├─────┐         " << std::endl;
            oss << "               └────────┘      └──────┘     │         " << std::endl;
            oss << "               ┌────────┐      ┌──────┐     │         " << std::endl;
            oss << "         ┌─────┤ Step 2 ├──────┤ NICK ├─────┘         " << std::endl;
            oss << "         │     └────────┘      └──────┘               " << std::endl;
            oss << "         │     ┌────────┐      ┌──────┐               " << std::endl;
            oss << "         └─────┤ Step 3 ├──────┤ USER ├─────┐         " << std::endl;
            oss << "               └────────┘      └──────┘     │         " << std::endl;
            oss << "         ┌──────────────────────────────────┘         " << std::endl;
            oss << "         │          ┌──────────┐                      " << std::endl;
            oss << "         └──────────┤ Use HELP ├────────────┐         " << std::endl;
            oss << "                    └──────────┘            │         " << std::endl;
            oss << "           ┌──────────────────────────────┐ │         " << std::endl;
            oss << "───────────┤ to learn each command syntax ├─┘         " << std::endl;
            oss << "           └──────────────────────────────┘           " << std::endl;
            oss << RESEND;
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
        case SHOWING_CHANNEL_TOPIC:
            oss << BRIGHT_MAGENTA BOLT << "You are seeing the topic of the channel: " << WHITE << _arguments[0] << RESEND;
            break;
        case CHANNEL_TOPIC_CHANGED:
            oss << BRIGHT_MAGENTA BOLT << "You are changing the topic of the channel: " << WHITE << _arguments[0] << RESEND;
            oss << BRIGHT_MAGENTA BOLT << "Now it is: " << WHITE << _arguments[1] << RESEND;
            break;
        case KICK_SOMEONE:
            oss << BRIGHT_MAGENTA BOLT << "You just kicked: " << WHITE << _arguments[1] << RESEND;
            oss << BRIGHT_MAGENTA BOLT << "He is no longer on server: " << WHITE << _arguments[0] << RESEND;
            break;
        case KICK_SOMEONE_MESSAGE:
            oss << BRIGHT_MAGENTA BOLT << "You just kicked: " << WHITE << _arguments[1] << RESEND;
            oss << BRIGHT_MAGENTA BOLT << "He is no longer on server: " << WHITE << _arguments[0] << RESEND;
            oss << BRIGHT_MAGENTA BOLT << "Kick message: " << WHITE << _arguments[2] << RESEND;
            break;
        case INVITE_SUCCESS:
            oss << BRIGHT_MAGENTA BOLT << "You invited " << WHITE << _arguments[0]
                << BRIGHT_MAGENTA BOLT << " to channel: " << WHITE << _arguments[1] << RESEND;
            break;
        case YOU_WERE_INVITED:
            oss << BRIGHT_MAGENTA BOLT << "You were invited by " << WHITE << _arguments[0]
                << BRIGHT_MAGENTA BOLT << " to join channel: " << WHITE << _arguments[1] << RESEND;
            break;
        case MODE_UPDATED:
            oss << BRIGHT_MAGENTA BOLT << "Channel mode updated: " << WHITE << _arguments[0] << " → " << _arguments[1] << RESEND;
            break;
        }
    }

    messageClient(oss.str());
}
