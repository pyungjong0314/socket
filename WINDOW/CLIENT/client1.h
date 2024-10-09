#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32")

#define PORT		8000
#define PACKET_SIZE	1024
#define SERVER_IP	"172.30.1.57"

using namespace std;

void client1();
