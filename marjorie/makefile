CC=g++
CFLAGS=-W -Wall -std=c++11 -pedantic -O3 
LDFLAGS=
EXEC=generate_activities persons_stats

all: $(EXEC)

persons_stats: main_write_persons_stats.o event.o activities.o activity.o person.o sha.o
	$(CC) -o persons_stats main_write_persons_stats.o event.o activities.o activity.o person.o sha.o $(LDFLAGS)

generate_activities: main_write_activities.o event.o activities.o activity.o sha.o
	$(CC) -o generate_activities main_write_activities.o event.o activities.o activity.o sha.o $(LDFLAGS)
	
main_write_activities.o: main_write_activities.cpp activities.hpp
	$(CC) -o main_write_activities.o -c main_write_activities.cpp $(CFLAGS)

event.o: event.cpp event.hpp
	$(CC) -o event.o -c event.cpp $(CFLAGS)
	
activity.o: activity.cpp activity.hpp event.hpp sha.hpp
	$(CC) -o activity.o -c activity.cpp $(CFLAGS)
	
activities.o: activities.cpp activities.hpp activity.hpp
	$(CC) -o activities.o -c activities.cpp $(CFLAGS)
	
main_write_persons_stats.o: main_write_persons_stats.cpp activity.hpp person.hpp
	$(CC) -o main_write_persons_stats.o -c main_write_persons_stats.cpp $(CFLAGS)
	
person.o: person.cpp person.hpp
	$(CC) -o person.o -c person.cpp $(CFLAGS)
	
sha.o: sha.cpp sha.hpp
	$(CC) -o sha.o -c sha.cpp $(CFLAGS)
		
clean:
	rm -rf *.o
rmproper: clean
	rm -rf $(EXEC)
