#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "worker.hpp"

using namespace std;

int main()
{
	Worker w("worker");

	w.Init();

	string req;
	while (true) {
		cin >> req;
		if (req == "stop") {
			break;
		}
		w.Request(req);
	}

	return 0;
}
