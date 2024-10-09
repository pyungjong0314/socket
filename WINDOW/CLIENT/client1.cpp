#include "client1.h"

void client1() {
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET hSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN tAddr = {};
	tAddr.sin_family = AF_INET;
	tAddr.sin_port = htons(PORT);
	inet_pton(AF_INET, SERVER_IP, &tAddr.sin_addr);

	connect(hSocket, (SOCKADDR*)&tAddr, sizeof(tAddr));

	cout << "START CLIENT" << endl;

	char cMsg[PACKET_SIZE] = {};
	char cBuffer[PACKET_SIZE] = {};

	while (cMsg[0] != '-') {
		cout << "SEND MSG: ";
		cin.getline(cMsg, PACKET_SIZE);
		send(hSocket, cMsg, PACKET_SIZE, 0);

		recv(hSocket, cBuffer, PACKET_SIZE, 0);

		cout << "RECV MSG: " << cBuffer << endl;
	}

	closesocket(hSocket);

	WSACleanup();
}