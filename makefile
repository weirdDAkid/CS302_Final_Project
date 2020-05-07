all: main

main: main.cpp Node.h ListInterface.h List.h
	g++ --std=c++11 -l /boost_1_66_0 main.cpp Node.h ListInterface.h List.h -o main

clean:
	rm main