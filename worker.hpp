#ifndef __WORKER_HPP__
#define __WORKER_HPP__

#include <thread>
#include <queue>
#include <mutex>
#include <atomic>
#include <condition_variable>

class Worker {
	private:
		std::string _name;
		std::thread *_thread;
		std::queue<std::string> _queue;
		std::mutex _mutex;
		std::condition_variable _cv;

		Worker(const Worker &);
		Worker& operator=(const Worker &);

		void Process();

	public:
		Worker(const std::string &);
		~Worker();
		void Init();
		void Stop();
		bool Request(const std::string &);
};

#endif
