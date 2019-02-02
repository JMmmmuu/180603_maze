CC = gcc
CFLAGS = -Wall -W -g
LIBS = -lncurses
OBJECTS = main.o cursor.o buildMaze.o DFSSearch.o

TARGET = maze

all: $(TARGET)

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)

clean:
	rm $(OBJECTS)
