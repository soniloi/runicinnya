LFLAGS = -Wall
CFLAGS = -Wall -c -O0 --std=c++11 -g
CC = clang++
COMPILE = $(CC) $(CFLAGS)
LINK = $(CC) $(LFLAGS)
OBJS = Building.o City.o Concave.o Court.o DirectionMappings.o Point.o Walkway.o Runicinnya.o

%.o: %.cpp %.h
	$(COMPILE) -c $<

lotalanta: $(OBJS)
	$(LINK) -o $@ $^

clean:
	rm -f *.o
