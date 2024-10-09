#include "server1.h"

void server1() {
	// Windows ���� ������ ���� ������ �����ϴ� �� ���Ǵ� WSADATA ������ ����
	WSADATA wsaData;
	// Windows ���� ������ �ʱ�ȭ�ϴ� �Լ�
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	// ������ �����ϴ� �Լ� (���Ͽ� ���� �ڵ��� ��ȯ)
	// PF_INET(IPv4 �ּ� �迭), SOCK_STREAM(��Ʈ�� ������ ���� ����), IPPROTO_TCP(TCP ��������)
	SOCKET hListen = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	// Windows ���� API���� ���ͳ� �ּҸ� ��Ÿ���� ���� ����(������ ���ε��� �ּ� �� ��Ʈ�� ���� ������ ����)
	SOCKADDR_IN tListenAddr = {};
	// ���ͳ� �ּ� �迭(IPv4)
	tListenAddr.sin_family = AF_INET;
	// ��Ʈ��ũ ����Ʈ ������ ��Ʈ ��ȣ ����
	tListenAddr.sin_port = htons(PORT);
	// ��Ʈ��ũ ����Ʈ ������ IP �ּҸ� ����
	inet_pton(AF_INET, SERVER_IP, &tListenAddr.sin_addr);


	// ������ Ư�� �ּ� �� ��Ʈ�� �����ϴ� �Լ�
	bind(hListen, (SOCKADDR*)&tListenAddr, sizeof(tListenAddr));
	// ���Ͽ��� ������ ������ ���� ����ϴ� �Լ�, SOMAXCONN(�ִ� ���� ��)
	listen(hListen, SOMAXCONN);

	cout << "START SERVER" << endl;

	// ���� Ŭ���̾�Ʈ�� �ּҿ� ���� ������ ������ ����
	SOCKADDR_IN tClntAddr = {};
	int iClntSize = sizeof(tClntAddr);
	// ���Ͽ��� ������ ������ �����ϴ� �Լ� (������ ������ ó���� ���Ͽ� ���� �ڵ��� ��ȯ)
	SOCKET hClient = accept(hListen, (SOCKADDR*)&tClntAddr, &iClntSize);

	// Ŭ���̾�Ʈ�� IP �ּ� ���
	char clientIp[INET_ADDRSTRLEN]; // IPv4 �ּ� ���̿� �´� ����
	inet_ntop(AF_INET, &tClntAddr.sin_addr, clientIp, sizeof(clientIp));
	cout << "Ŭ���̾�Ʈ IP �ּ�: " << clientIp << std::endl;

	// Ŭ���̾�Ʈ�κ��� ���� �����͸� �����ϴ� ����
	char cBuffer[PACKET_SIZE] = {};
	char cMsg[PACKET_SIZE] = {};

	while (1) {
		// ���Ͽ��� �����͸� �޴� �Լ�
		recv(hClient, cBuffer, PACKET_SIZE, 0);
		cout << "RESV MSG: " << cBuffer << endl;

		cout << "SEND MSG: ";
		cin.getline(cMsg, PACKET_SIZE);
		// �����͸� �������� ������ �Լ� ȣ��
		send(hClient, cMsg, PACKET_SIZE, 0);
	}

	closesocket(hClient);
	closesocket(hListen);

	// ���� ������ ����� �����ϴ� �Լ�
	WSACleanup();
}