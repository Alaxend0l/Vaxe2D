#include "apps/app_chip8.h"

// std
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <fstream>

vaxe::vApp_Chip8 app{};

std::string romPath = "../roms/chip-8/test_opcode.ch8";
size_t romSize;


unsigned char* loadRom()
{
	std::ifstream romFile;

	romFile.open(romPath.c_str(), std::ios::in | std::ios::binary);
	romFile.seekg(0, std::ios::end);

    romSize = romFile.tellg();

	unsigned char* data = (unsigned char*)malloc(romSize + 1);
	data[romSize] = '\0';

	romFile.seekg(0, std::ios::beg);
	romFile.read(reinterpret_cast<char *>(data), romSize);

	romFile.close();

	return data;
}

int main(int argc, char **argv)
{
	app.rom = loadRom();
	app.romSize = romSize;

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

