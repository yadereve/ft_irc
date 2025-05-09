#include "../includes/Server.hpp"

volatile sig_atomic_t run = true;

void signalHandler(int)
{
	run = false;
}

int main(int ac, char* av[])
{
	try
	{
		if (ac != 3)
			throw std::invalid_argument("Usage: ./irserv <port> <password>");

		std::cout << "---------------SERVER---------------\n";

		parseInput(av[1], av[2]);
		signal(SIGINT, signalHandler);
		Server server(av[1], av[2]);
		server.start();
		std::cout << BLUE << "\n>>> The Server Closed! <<<" << RESET << std::endl;
		return 0;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}
