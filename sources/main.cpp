#include "../includes/Server.hpp"

int main(int ac, char* av[])
{
	try
	{
		if (ac != 3)
			throw std::invalid_argument("Usage: ./irserv <port> <password>");

		std::cout << "---------------SERVER---------------\n";

		parseInput(av[1], av[2]);
		signal(SIGPIPE, SIG_IGN);
		Server server(av[1], static_cast<std::string>(av[2]));
		server.start();
		std::cout << BLUE << ">>> The Server Closed! <<<" << RESET << std::endl;
		return 0;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	catch (...)
	{
		std::cerr << "Exception occurred" << std::endl;
		return 2;
	}

	return 0;
}
