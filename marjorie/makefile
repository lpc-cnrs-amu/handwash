CC=g++
CFLAGS=-W -Wall -std=c++11 -pedantic -O3 
LDFLAGS=
EXEC=generate_activities

all: $(EXEC)

generate_activities: main.o event.o activities.o activity.o
	$(CC) -o generate_activities main.o event.o activities.o activity.o $(LDFLAGS)
	
main.o: main.cpp activities.hpp
	$(CC) -o main.o -c main.cpp $(CFLAGS)

event.o: event.cpp event.hpp
	$(CC) -o event.o -c event.cpp $(CFLAGS)
	
activity.o: activity.cpp activity.hpp event.hpp
	$(CC) -o activity.o -c activity.cpp $(CFLAGS)
	
activities.o: activities.cpp activities.hpp activity.hpp
	$(CC) -o activities.o -c activities.cpp $(CFLAGS)

clean:
	rm -rf *.o
rmproper: clean
	rm -rf $(EXEC)
