#include <iostream>
#include <elfio/elfio.hpp>
#include <ario/ario.hpp>
int main() {
	ELFIO::elfio reader;
	if (reader.load("my_binary.elf")) {
		// Access ELF sections, segments, symbols, etc.
	}
	std::cout << "HELLO WORLD" << std::endl;

	return 0;
}