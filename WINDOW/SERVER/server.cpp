#include "server1.h"
#include "server2.h"
#include "server3.h"

int main(void) {

	int version;

	cout << "SELECT SERVER VERSION: ";
	cin >> version;
	cin.ignore();

	if (version == 1) {
		server1();
	}
	else if (version == 2) {
		server2();
	}
	else if (version == 3) {
		server3();
	}

	return 0;
}