#include <iostream>
#include "worker.hpp"

using namespace std;

Worker::Worker(const string &name): _name(name), _thread(NULL)
{
}

Worker::~Worker()
{
	Stop();
}

void Worker::Init()
{
	if (NULL == _thread) {
		_thread = new thread(&Worker::Process, this);
	}
}

void Worker::Stop()
{
	if (NULL == _thread) {
		return;
	}

	{
		Request("stop");
		_thread->join();
		delete _thread;
		_thread = NULL;
	}
}

bool Worker::Request(const string &req)
{
	if (NULL == _thread) {
		return false;
	}

	std::unique_lock<std::mutex> lk(_mutex);
	_queue.push(req);
	_cv.notify_one();

	return true;
}

void Worker::Process()
{
	while (true) {
		string req;
		{
			std::unique_lock<std::mutex> lk(_mutex);

			while (_queue.empty()) {
				_cv.wait(lk);
			}

			if (_queue.empty()) {
				continue;
			}

			req = _queue.front();
			_queue.pop();
		}

		if (req == "stop") {
			break;
		}

		cout << "processing: " << req << endl;
	}
}
