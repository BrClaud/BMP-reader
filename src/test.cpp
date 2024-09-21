#include <iostream>

int main() {
	std::cout << "\033[30;47mThis text is black\033[0m" << std::endl;
	std::cout << "\033[30;47m  \033[0m" << std::endl;  // белый
	return 0;
}