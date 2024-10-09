#include "server3.h"

void server3() {
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET hListen = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN tListenAddr = {};
	tListenAddr.sin_family = AF_INET;
	tListenAddr.sin_port = htons(PORT);
	tListenAddr.sin_addr.s_addr = htonl(INADDR_ANY);


	bind(hListen, (SOCKADDR*)&tListenAddr, sizeof(tListenAddr));
	listen(hListen, SOMAXCONN);

	cout << "START SERVER" << endl;

	SOCKADDR_IN tClntAddr = {};
	int iClntSize = sizeof(tClntAddr);
	SOCKET hClient = accept(hListen, (SOCKADDR*)&tClntAddr, &iClntSize);

	char clientIp[INET_ADDRSTRLEN]; // IPv4 �ּ� ���̿� �´� ����
	inet_ntop(AF_INET, &tClntAddr.sin_addr, clientIp, sizeof(clientIp));
	cout << "Ŭ���̾�Ʈ IP �ּ�: " << clientIp << std::endl;

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