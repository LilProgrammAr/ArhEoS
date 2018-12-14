#include <winsock2.h>
#include <iostream>
#include <chrono>
#include <string>
#include <windows.h>
#include <filesystem>
#include <fstream>

#pragma warning(disable:4996)

constexpr auto INIT_ERROR = 1;
constexpr auto PORT = 1031ui16;
constexpr auto ADDR = "127.0.0.1";
constexpr auto MESSAGE_SIZE = 2000;

std::string parse(std::string mess);
std::string get_entries(std::string filter);
bool check_name(std::string name, std::string filter);

std::ofstream logst;

void log(std::string log);

int main(int argc, char* argv[]) {
	{
		std::string curpath = argv[0];
		auto path = std::filesystem::path(std::wstring(curpath.begin(), curpath.end())).parent_path();
		std::filesystem::current_path(path);
	}
	logst.open("server_log.txt");
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

	if (bind(s, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
		std::cout << "\nbind() failed\n";
		closesocket(s);
		WSACleanup();
		system("pause");
		return SOCKET_ERROR;
	}

	if (listen(s, 1) == SOCKET_ERROR) {
		std::cout << "\nError listening socket\n";
		closesocket(s);
		WSACleanup(); system("pause");
		return SOCKET_ERROR;
	}

	std::cout << "Waiting for client to connect...\n";
	while (true) {
		SOCKET as;
		as = SOCKET_ERROR;
		while (as == SOCKET_ERROR) {
			as = accept(s, nullptr, nullptr);
		}
		std::cout << "Connected to " << ADDR << "::" << PORT << " !\n";
		s = as;
		break;
	}

	char recvbuf[MESSAGE_SIZE] = "";
	int byterecv;
	while (true) {
		byterecv = recv(s, recvbuf, MESSAGE_SIZE, 0);
		log(std::string("Got -> ").append(recvbuf));
		if (byterecv == 0 || byterecv == WSAECONNRESET) {
			std::cout << "Connection closed\n";
			break;
		}
		auto resp = parse(recvbuf);
		std::cout << "Got -> " << recvbuf << std::endl;
		if (resp.empty()){
			std::cout << "Connection closed\n";
			send(s, "", 0, 0);
			break;
		}
		else 
			send(s, resp.c_str() , strlen(resp.c_str()), 0);
		std::cout << "Sent -> " << resp << std::endl;
		log(std::string("Sent -> ").append(resp));
	}
	WSACleanup();
	logst.close();
	//system("pause");
	return 0;
}

std::string parse(std::string mess) {
	{
		if (mess.find("Who") != std::string::npos)
			return "Herashchenko Serhii, K-26, #6: files list";
	}
	{
		int pos = mess.find("show_entries");
		if (pos != std::string::npos) {
			if (mess.length() < pos + 13)
				return get_entries("");
			return get_entries(mess.substr(pos + 13));
		}
	}
	{
		if (mess.find("exit") != std::string::npos)
			return "";
	}
	return "Wrong command";
}

std::string get_entries(std::string filter) {
	namespace fs = std::filesystem;
	std::string res = "Entries in current server directory:\n";
	for (auto entry : fs::directory_iterator(fs::current_path())) {
		auto t = std::wstring(entry.path().filename().c_str());
		std::string str(t.begin(), t.end());
		if (check_name(str, filter)) {
			res.append(std::string(t.begin(), t.end()));
			res.push_back('\n');
		}
	}
	return res;
}

bool check_name(std::string name, std::string filter) {
	if (filter.empty())
		return true;
	return name.find(filter) != std::string::npos;
}

void log(std::string log) {
	using namespace std::chrono;
	auto t = system_clock::to_time_t(system_clock::now());
	logst << std::ctime(&t) << ": " << log << std::endl;
}