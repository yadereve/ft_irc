#include "../../../includes/Client.hpp"
#include <cstddef>
#include <string>

void Client::bot(std::ostringstream &oss)
{
    oss << CYAN << "├─ " << CYAN BOLT << "BOT <token>" << std::endl;
    oss << CYAN << "│" << WHITE << "\tBOT" << std::endl;
}

int Client::bot()
{
    std::string arg;
	std::string cmd;
    if (_arguments.size() < 1)
        arg = "Usage: BOT :<command>";
    else
		cmd = _arguments[0];
	
	if (cmd == "help")
		arg = "Avilable commands: HELP, TIME, JOKE, ECHO";
	else if (cmd == "echo")
	{
		for (size_t i = 1; i < _arguments.size(); ++i)
			arg += _arguments[i] + " ";
	}
	messageClient(":Bot PRIVMSG " + _nick + " :" + arg + "\r\n");
    return 0;
}
