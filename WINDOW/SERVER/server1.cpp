#include "server1.h"

void server1() {
	// Windows 소켓 구현에 대한 정보를 저장하는 데 사용되는 WSADATA 유형의 변수
	WSADATA wsaData;
	// Windows 소켓 구현을 초기화하는 함수
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	// 소켓을 생성하는 함수 (소켓에 대한 핸들을 반환)
	// PF_INET(IPv4 주소 계열), SOCK_STREAM(스트림 소켓인 소켓 유형), IPPROTO_TCP(TCP 프로토콜)
	SOCKET hListen = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	// Windows 소켓 API에서 인터넷 주소를 나타내기 위한 구조(소켓이 바인딩될 주소 및 포트에 대한 정보를 저장)
	SOCKADDR_IN tListenAddr = {};
	// 인터넷 주소 계열(IPv4)
	tListenAddr.sin_family = AF_INET;
	// 네트워크 바이트 순서로 포트 번호 지정
	tListenAddr.sin_port = htons(PORT);
	// 네트워크 바이트 순서로 IP 주소를 지정
	inet_pton(AF_INET, SERVER_IP, &tListenAddr.sin_addr);


	// 소켓을 특정 주소 및 포트와 연결하는 함수
	bind(hListen, (SOCKADDR*)&tListenAddr, sizeof(tListenAddr));
	// 소켓에서 들어오는 연결을 수신 대기하는 함수, SOMAXCONN(최대 연결 수)
	listen(hListen, SOMAXCONN);

	cout << "START SERVER" << endl;

	// 연결 클라이언트의 주소에 대한 정보를 수신할 구조
	SOCKADDR_IN tClntAddr = {};
	int iClntSize = sizeof(tClntAddr);
	// 소켓에서 들어오는 연결을 수락하는 함수 (들어오는 연결을 처리할 소켓에 대한 핸들을 반환)
	SOCKET hClient = accept(hListen, (SOCKADDR*)&tClntAddr, &iClntSize);

	// 클라이언트의 IP 주소 출력
	char clientIp[INET_ADDRSTRLEN]; // IPv4 주소 길이에 맞는 버퍼
	inet_ntop(AF_INET, &tClntAddr.sin_addr, clientIp, sizeof(clientIp));
	cout << "클라이언트 IP 주소: " << clientIp << std::endl;

	// 클라이언트로부터 받은 데이터를 저장하는 버퍼
	char cBuffer[PACKET_SIZE] = {};
	char cMsg[PACKET_SIZE] = {};

	while (1) {
		// 소켓에서 데이터를 받는 함수
		recv(hClient, cBuffer, PACKET_SIZE, 0);
		cout << "RESV MSG: " << cBuffer << endl;

		cout << "SEND MSG: ";
		cin.getline(cMsg, PACKET_SIZE);
		// 데이터를 소켓으로 보내는 함수 호출
		send(hClient, cMsg, PACKET_SIZE, 0);
	}

	closesocket(hClient);
	closesocket(hListen);

	// 소켓 구현의 사용을 종료하는 함수
	WSACleanup();
}