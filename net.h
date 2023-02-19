#pragma once
#pragma warning(disable: 4996)
#pragma comment(lib, "ws2_32.lib")

#include <iostream>
#include <WinSock2.h>

namespace net {
	class net {
	protected:
		WSAData wsa_data;
		WORD dll_version;
		SOCKADDR_IN socket_address;

		int socket_address_size;
	public:
		net() {
			dll_version = MAKEWORD(2, 1);
			if (WSAStartup(dll_version, &wsa_data) != 0)
				std::cout << "\"WinSock2.h\" not start (line " << __LINE__ << ")\n";

			socket_address_size = sizeof(socket_address);
			socket_address.sin_addr.s_addr = inet_addr("127.0.0.1");
			socket_address.sin_port = htons(7474);
			socket_address.sin_family = AF_INET;
		}
		~net() {

		}
	};
	class server : net {
	private:
		SOCKET socket_listen;
		SOCKET socket_client[4];

		int sc_number = 0;
	public:
		server(int _port = 7474) {
			socket_address.sin_port = _port;
			socket_listen = socket(AF_INET, SOCK_STREAM, NULL);
			bind(socket_listen, (SOCKADDR*)&socket_address, sizeof(socket_address));
			listen(socket_listen, SOMAXCONN);
		}
		void new_client() {
			socket_client[sc_number] = accept(socket_listen, (SOCKADDR*)&socket_address, &socket_address_size);
			if (socket_client == 0) {
				std::cout << "Client has not connection\n";
			}
			sc_number++;
		}
		void send(const char _message[256], int _sc_number) {
			::send(socket_client[_sc_number], _message, 256, NULL);
			return;
		}
		char* recv(int _sc_number) {
			char message[256];
			::recv(socket_client[_sc_number], message, 256, NULL);
			return message;
		}
		~server() {

		}
	};

	class client : net {
	private:
		SOCKET socket_client;
	public:
		client(int _port = 7474) {
			socket_address.sin_port = _port;
			socket_client = socket(AF_INET, SOCK_STREAM, NULL);
			if (connect(socket_client, (SOCKADDR*)&socket_address, sizeof(socket_address))) {
				std::cout << "Client has not connection";
			}
		}
		void send(char message[256]) {
			::send(socket_client, message, 256, NULL);
			return;
		}
		char* recv() {
			char message[256];
			::recv(socket_client, message, 256, NULL);
			return message;
		}
		~client() {

		}
	};
}