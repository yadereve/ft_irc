#include "../includes/Server.hpp"

int main(int ac, char* av[])
{
	if (ac != 3)
	{
		std::cerr << "Invalid argument\n";
		return 1;
	}
	
	std::cout << "----------SRVER----------\n";

	Server server(av[1], av[2]);

	try
	{
		server.start();
		return 0;
	}
	catch (const std::exception& e)
	{
		server.closeFds();
		std::cerr << e.what() << std::endl;
		return 1;
	}
	std::cout << BLUE << ">>> The Server Closed! <<<" << RESET << std::endl;
}
