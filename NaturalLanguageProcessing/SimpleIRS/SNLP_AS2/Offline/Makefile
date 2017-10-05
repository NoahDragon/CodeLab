CC = g++

CFLAGS = 

OBJS = ReadDoc.o Offline.o

Offline: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o offline -lfl

Offline.o: Offline.cpp global.h ReadDoc.h Offline.h
	$(CC) $(CFLAGS) -c Offline.cpp
	
ReadDoc.o: ReadDoc.cpp ReadDoc.h global.h
	$(CC) $(CFLAGS) -c ReadDoc.cpp


clean:
	rm -f offline $(OBJS)
