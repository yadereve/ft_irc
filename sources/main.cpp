#include "../includes/Server.hpp"

int main(int ac, char* av[])
{
	if (ac != 3)
	{
		std::cerr << "Invalid argument\n";
		return 1;
	}
	std::string password(av[2]);
	std::cout << "port: " << av[1] << std::endl;
	std::cout << "password: ";
	for (size_t i = 0; i < password.length(); i++)
		std::cout << '*';
	std::cout << std::endl;

	Server server(av[1], av[2]);

	try
	{
		server.start();
		return 0;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
}
