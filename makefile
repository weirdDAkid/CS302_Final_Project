all: main

main: main.cpp Node.h ListInterface.h List.h
	g++ --std=c++11 main.cpp Node.h ListInterface.h List.h -o main

clean:
	rm main