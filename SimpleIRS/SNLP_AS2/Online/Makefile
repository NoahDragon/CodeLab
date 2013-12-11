CC = g++

CFLAGS = 

OBJS =  Util.o Loaddata.o Weight.o IRS.o

IRS: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o IRS

IRS.o: IRS.cpp Loaddata.h Weight.h Util.h global.h
	$(CC) $(CFLAGS) -c IRS.cpp

Loaddata.o: Loaddata.cpp global.h Util.h Loaddata.h
	$(CC) $(CFLAGS) -c Loaddata.cpp

Weight.o: Weight.cpp Weight.h global.h
	$(CC) $(CFLAGS) -c Weight.cpp

Util.o:  Util.cpp Util.h global.h
	$(CC) $(CFLAGS) -c Util.cpp


clean:
	rm -f IRS $(OBJS)
