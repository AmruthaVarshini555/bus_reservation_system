all: busreservationsystem

busreservationsystem: main.o menu.o bus.o ticket.o
        g++ main.o menu.o bus.o ticket.o -o busreservationsystem

main.o: main.cpp
        g++ -c menu.h main.cpp

bus.o: bus.cpp
        g++ -c bus.h bus.cpp

ticket.o: ticket.cpp
        g++ -c ticket.h ticket.cpp

clean:
        rm *.o
        rm *.gch
