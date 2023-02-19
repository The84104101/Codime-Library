#include <thread>
#include <conio.h>
#include "net.h"

void new_client(net::server _s) {
	for (int i = 0; i < 4; i++) {
		_s.new_client();

		std::cout
			<< "Client has connected\n";

		_s.send("Hello world!", i);
	}

	return;
}

int main(void) {
	std::cout
		<< "Codime library\n"
		<< "net.h example\n"
		<< '\n'
		<< "Server or Client mode? (s/c): ";

	char key = getch();

	if (key == 's') {
		std::cout
			<< '\n'
			<< "Server mode\n";

		net::server s;
		std::thread nc_t(new_client, s);
		nc_t.join();

		return 0;
	}
	if (key == 'c') {
		std::cout
			<< '\n'
			<< "Client mode\n";

		net::client c;
		std::string message = c.recv();
		std::cout << message << '\n';

		return 0;
	}

	return 0;
}