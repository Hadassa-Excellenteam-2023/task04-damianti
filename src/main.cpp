#include <iostream>
#include <exception>
#include <exception>

#include "Controller.h"

int main() {
	
	try {

		Controller controller = Controller();
		controller.run();

	}
	catch (const std::exception& e) {
		std::cerr << e.what();
	}
	
	std::cout << "Bye\n";


	return 0;

}