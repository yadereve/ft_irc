#include "../../includes/Client.hpp"

Client::Client(Server &server, int s) : _server(server), _socket(s)
{
    _pass_check = false;
    _nick_check = false;
    _user_check = false;
    _authenticated_check = false;
	resolveHostname();
    printMessage(FIRST_MESSAGE);
}

Client::~Client()
{
}

/* methods */

void Client::messageClient(std::string msg)
{
    send(_socket, msg.c_str(), msg.length(), 0);
}

void Client::messageClient(int nb)
{
    std::ostringstream oss;
    oss << nb;
    std::string msg = oss.str();
    send(_socket, msg.c_str(), msg.length(), 0);
}

bool Client::validName(std::string str)
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

bool Client::channelExist(std::string channel_name)
{
    const std::vector<Channel> &channel_list = _server.getChannelList();

    std::vector<Channel>::const_iterator it;
    for (it = channel_list.begin(); it != channel_list.end(); ++it)
    {
        if (it->getName() == channel_name)
            return true;
    }
    return false;
}

bool Client::nickExist(std::string nick)
{
    const std::vector<std::string> &nick_list = _server.getNickList();

    std::vector<std::string>::const_iterator it;
    for (it = nick_list.begin(); it != nick_list.end(); ++it)
    {
        if (*it == nick)
            return true;
    }
    return false;
}

void Client::executeCommand(std::string input)
{
	DEBUG("input: \n" << input);
	for (size_t i = 0; i < input.length(); ++i)
	{
		_input += input[i];
		if (input[i] == '\n')
		{
			// reset command and arguments
			_cmd.clear();
			_arguments.clear();

			// transform input into a legible command
			size_t command_id = parser(_input);

			// execute command by id
			int return_message = commandHandler(command_id);

			// print return message
			printMessage(return_message);
			_input.clear();
		}
	}
}

/* setters */

//void Client::setSocket(int s) { _socket = s; }

/* getters */

int Client::getSocket() { return _socket; }

//add for channel

std::string Client::getNickname() const {
    return _nick;
}

void Client::receiveMessage(const std::string &source, const std::string &command, const std::string &args) {
    std::string msg = ":" + source + " " + command + " " + args + "\r\n";
    messageClient(msg);
}

void Client::printMessage(int messageId, const std::string& arg1, const std::string& arg2)
{
    _arguments.clear();
    _arguments.push_back(arg1);
    _arguments.push_back(arg2);
    printMessage(messageId);
}

void Client::resolveHostname() {
    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);

    if (getpeername(_socket, (struct sockaddr*)&addr, &addr_len) == 0) {
        _hostname = inet_ntoa(addr.sin_addr);  // IP as string
    } else {
        _hostname = "unknown";
    }
}

std::string Client::getFullMask() const {
    return _nick + "!" + _user + "@" + _hostname;
}

void Client::sendJoinMessages(const std::string& channel_name, Channel* channel) {
	std::string hostname = _server.getHostname();
	std::string full_mask = getFullMask();

	// Current timestamp for @time in HexChat format
	std::ostringstream timestamp;
	timestamp << "@time=" << std::time(0);  // Unix timestamp
	std::string time_str = timestamp.str();

	std::cout << "Hostname: " << hostname << std::endl;

	// JOIN message
	messageClient(":" + full_mask + " JOIN :" + channel_name + "\r\n");

	// Channel MODE (324)
	messageClient(":" + hostname + " 324 " + _nick + " " + channel_name + " +nt\r\n");

	// Channel creation time (329)
	std::ostringstream ts;
	ts << ":" << hostname << " 329 " << _nick << " " << channel_name << " " << std::time(0) << "\r\n";
	messageClient(ts.str());

	// Names list (353)
	std::string names_line;
	const std::map<std::string, Client*>& clients = channel->getClients();
	for (std::map<std::string, Client*>::const_iterator it = clients.begin(); it != clients.end(); ++it) {
		Client* client = it->second;
		if (channel->isOperator(client))
			names_line += "@" + client->getNickname() + " ";
		else
			names_line += client->getNickname() + " ";
	}
	messageClient(":" + hostname + " 353 " + _nick + " = " + channel_name + " :" + names_line + "\r\n");

    // End of NAMES list (366)
    messageClient(":" + hostname + " 366 " + _nick + " " + channel_name + " :End of /NAMES list.\r\n");

    // Additional WHO information
    messageClient(":" + hostname + " 354 " + _nick + " 152 " + channel_name + " ~" + _nick + " 62.28.170.40 " + hostname + " " + _nick + " H@ 0 :realname\r\n");

    // End of WHO list (315)
    messageClient(":" + hostname + " 315 " + _nick + " " + channel_name + " :End of /WHO list\r\n");
}
