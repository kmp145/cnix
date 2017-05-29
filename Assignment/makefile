CC = gcc
CFLAGS = -Wall

TARGET = aLockAssignmet

default: $(TARGET) 

$(TARGET): files.o io.o logger.o networking.o
	gcc -Wall files.o io.o logger.o networking.o -o $(TARGET)

files.o: files.c io.h logger.h files.h
	$(CC) $(CFLAGS) -c files.c

io.o: io.c io.h
	$(CC) $(CFLAGS) -c io.c

networking.o: networking.c networking.h logger.h
	$(CC) $(CFLAGS) -c networking.c

logger.o: logger.c logger.h
	$(CC) $(CFLAGS) -c logger.c

clean: 
	$(RM) files *.o


