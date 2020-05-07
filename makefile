all: main

main: main.cpp
	g++ --std=c++11 -I /home/lizzybethas64/CS302/proj_f/boost_1_66_0 main.cpp -o main

clean:
	rm main