#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32")

#define PACKET_SIZE	1024

using namespace std;

void client2();
