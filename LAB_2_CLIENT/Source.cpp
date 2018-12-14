#include <winsock2.h>
#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include <ctime>

#pragma warning(disable:4996) 

constexpr auto INIT_ERROR = 1;
constexpr auto PORT = 1031ui16;
constexpr auto ADDR = "127.0.0.1";//"192.168.1.199";
constexpr auto MESSAGE_SIZE = 2000;

std::ofstream logst;

void log(std::string log);

int main(int argc, char* argv[]) {
	logst.open("client_log.txt");
	WSADATA wsa_socket;
	SOCKET s;
	if (WSAStartup(0x0202, &wsa_socket) != 0) {
		std::cout << "\nSocket_Server()> open WSAStartup is invalid!\n";
		WSACleanup();
		system("pause");
		return INIT_ERROR;
	}

	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s == INVALID_SOCKET) {
		std::cout << "\nCannot create socket\n";
		WSACleanup();
		system("pause");
		return INVALID_SOCKET;
	}

	//Successfull initialization
	sockaddr_in service;
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = inet_addr(ADDR);
	service.sin_port = htons(PORT);

	if (connect(s, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
		std::cout << "Error connecting to the server\n";
		WSACleanup();
		system("pause");
		return SOCKET_ERROR;
	}
	
	std::cout << "Connected to " << ADDR << "::" << PORT << " !\n";

	std::string mess;
	while (getline(std::cin, mess)) {
		send(s, mess.c_str(), MESSAGE_SIZE, 0);
		log(std::string("Sent -> ").append(mess));
		char recvbuf[MESSAGE_SIZE] = "";
		int byterecv;
		while (true) {
			byterecv = recv(s, recvbuf, MESSAGE_SIZE, 0);
			if (byterecv == 0 || byterecv == WSAECONNRESET || mess == "exit") {
				std::cout << "Connection closed\n";
				WSACleanup();
				system("pause");
				return 0;
			}
			std::string response("Got -> ");
			response.append(recvbuf);
			std::cout << response << std::endl;
			log(response);
			break;
		}
	}
	WSACleanup();
	logst.close();
	system("pause");
	return 0;
}

void log(std::string log) {
	using namespace std::chrono;
	auto t = system_clock::to_time_t(system_clock::now());
	logst << std::ctime(&t) << ": " << log << std::endl;
}