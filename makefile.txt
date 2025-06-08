main: main.o hexlib.o
	g++ main.o hexlib.o -o main
	
main.o: main.cpp
	g++ -c main.cpp
	
hexlib.o: hexlib.cpp
	g++ -c hexlib.cpp
	
clean:
	rm *.o main