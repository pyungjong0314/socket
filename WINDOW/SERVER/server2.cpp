#include "server2.h"

int PORT;
char SERVER_IP[16];

void server2() {
	cout << "PORT: ";
	cin >> PORT;
	cout << "IP: ";
	cin >> SERVER_IP;
	cin.ignore();

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET hListen = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN tListenAddr = {};
	// 인터넷 주소 계열(IPv4)
	tListenAddr.sin_family = AF_INET;
	tListenAddr.sin_port = htons(PORT);
	inet_pton(AF_INET, SERVER_IP, &tListenAddr.sin_addr);


	// 소켓을 특정 주소 및 포트와 연결하는 함수
	bind(hListen, (SOCKADDR*)&tListenAddr, sizeof(tListenAddr));
	listen(hListen, SOMAXCONN);

	cout << "START SERVER" << endl;

	SOCKADDR_IN tClntAddr = {};
	int iClntSize = sizeof(tClntAddr);
	SOCKET hClient = accept(hListen, (SOCKADDR*)&tClntAddr, &iClntSize);

	// 클라이언트의 IP 주소 출력
	char clientIp[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &tClntAddr.sin_addr, clientIp, sizeof(clientIp));
	cout << "클라이언트 IP 주소: " << clientIp << std::endl;

	char cBuffer[PACKET_SIZE] = {};
	char cMsg[PACKET_SIZE] = {};

	while (1) {
		recv(hClient, cBuffer, PACKET_SIZE, 0);
		cout << "RESV MSG: " << cBuffer << endl;

		cout << "SEND MSG: ";
		cin.getline(cMsg, PACKET_SIZE);

		send(hClient, cMsg, PACKET_SIZE, 0);
	}

	closesocket(hClient);
	closesocket(hListen);

	WSACleanup();
}