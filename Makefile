OPCIONS = -D_GLIBCXX_DEBUG -Wall -Wno-deprecated -Wextra -Werror -std=c++11

main: main.o cambra.o laberint.o
	g++ -o main main.o cambra.o laberint.o -lesin
	rm *.o

main.o: main.cpp
	g++ -c main.cpp $(OPCIONS)

cambra.o: cambra.cpp
	g++ -c cambra.cpp $(OPCIONS)

laberint.o: laberint.cpp
	g++ -c laberint.cpp $(OPCIONS)

clean:
	rm *.o
	rm *.exe
	rm *.gch