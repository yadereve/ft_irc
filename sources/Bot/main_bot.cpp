#include "../../includes/Bot.hpp"

int main(int ac, char** av)
{
	if (ac != 3)
	{
		std::cerr << "Usege: ./ircbot <port> <server_password>" << std::endl;
		return -1;
	}

	int port = std::atoi(av[1]);
	std::string pass = av[2];
	Bot bot("127.0.0.1", port, pass, "FunBot", "FunBot_", "#general");
	bot.run();

	return 0;
}
