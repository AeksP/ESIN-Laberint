OPCIONS = -Wall -Werror -Wextra -Wno-implicit-fallthrough -ansi

driver_maze: driver_maze.o cambra.o laberint.o teseus.o dedalus.o
	g++ -o driver_maze driver_maze.o cambra.o laberint.o teseus.o dedalus.o -lesin
	rm *.o

driver_maze.o: driver_maze.cpp
	g++ -c driver_maze.cpp $(OPCIONS)

cambra.o: cambra.cpp
	g++ -c cambra.cpp $(OPCIONS)

laberint.o: laberint.cpp
	g++ -c laberint.cpp $(OPCIONS)

teseus.o: teseus.cpp
	g++ -c teseus.cpp $(OPCIONS)

dedalus.o: dedalus.cpp
	g++ -c dedalus.cpp $(OPCIONS)

clean:
	rm *.o
	rm *.exe
	rm *.gch