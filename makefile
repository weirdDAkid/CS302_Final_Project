all: main

main: main.cpp Node.h ListInterface.h List.h
	g++ --std=c++11 -l main.cpp Node.h ListInterface.h List.h boost/graph/graph_traits.hpp -o main

clean:
	rm main