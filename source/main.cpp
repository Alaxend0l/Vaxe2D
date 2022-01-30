#include "apps/app_first.h"
#include "apps/app_second.h"

// std
#include <cstdlib>
#include <iostream>
#include <stdexcept>

int main()
{
    vaxe::vApp_Second app{};

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