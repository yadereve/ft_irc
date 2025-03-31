#include "../includes/Server.hpp"
#include <stdexcept>

int main(int ac, char* av[])
{
	try
	{
		if (ac != 3)
			throw std::runtime_error("Usage: ./irserv <port> <password>");

		std::cout << "----------SERVER----------\n";

		Server server(av[1], av[2]);
		server.start();
		std::cout << BLUE << ">>> The Server Closed! <<<" << RESET << std::endl;
		return 0;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
}
