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
		w.Request(req);
	}

	return 0;
}
