CFLAGS += -std=c++11 -lpthread

all: main.cpp worker.cpp
	$(CXX) -o main $(CFLAGS) $^

clean:
	rm main

