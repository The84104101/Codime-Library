#include <iostream>
#include <thread>
#include <conio.h>
#include "net.h"

int main(void) {
	char key = getch();

	if (key == 's') {
		net::server s;
		
		s.new_client();
		s.send("Hi!", 0);
	}
	if (key == 'c') {
		net::client c;
		c.recv();
	}

	return 0;
}