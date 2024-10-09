#include "client1.h"
#include "client2.h"

int main(void) {
	int num;
	cout << "SELECT CLIENT VERSION: ";
	cin >> num;
	cin.ignore();

	if (num == 1) {
		client1();
	}
	else if (num == 2) {
		client2();
	}

	return 0;
}