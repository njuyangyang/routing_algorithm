all:main.o generators.o set_operations.o heapSort.o routing_alg.o
	g++ -std=c++11 main.o generators.o set_operations.o heapSort.o routing_alg.o -o main

main.o:main.cpp
	g++ -std=c++11 -c main.cpp

generators.o:generators.cpp
	g++ -std=c++11 -c generators.cpp

set_operations.o:set_operations.cpp
	g++ -std=c++11 -c set_operations.cpp

heapSort.o:heapSort.cpp
	g++ -std=c++11 -c heapSort.cpp

routing_alg.o:routing_alg.cpp
	g++ -std=c++11 -c routing_alg.cpp

clean:
	rm -rf *.o main *.txt