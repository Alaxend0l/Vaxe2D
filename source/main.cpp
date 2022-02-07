#include "apps/app_chip8.h"

// std
#include <cstdlib>
#include <iostream>
#include <stdexcept>

int main()
{
    vaxe::vApp_Chip8 app{};

	try
	{
		app.Run();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}