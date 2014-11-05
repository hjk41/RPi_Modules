CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lrt
SOURCES=RPi_GPIO.cpp TestDist.cpp Read.cpp Set.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=TestDist Read Set


all: $(EXECUTABLE)

TestDist: TestDist.o RPi_GPIO.o
	$(CC) $(LDFLAGS) RPi_GPIO.o $< -o $@

Read: Read.o RPi_GPIO.o
	$(CC) $(LDFLAGS) RPi_GPIO.o $< -o $@

Set: Set.o RPi_GPIO.o
	$(CC) $(LDFLAGS) RPi_GPIO.o $< -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o
	rm -f $(EXECUTABLE)
