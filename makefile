all: driver.o

driver.o: driver.cpp BinarySearchTree.h BinaryTreeInterface.h BinaryNode.h
	g++ --std=c++11 driver.cpp BinarySearchTree.h BinaryTreeInterface.h BinaryNode.h -o driver.o

clean:
	rm driver