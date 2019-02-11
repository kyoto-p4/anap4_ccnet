all: anap4.c kinelib.o startup.o dataclient.o histdef.o anaevt.o anap4.h
	$(CC) -o anap4 anap4.c kinelib.o startup.o dataclient.o \
                histdef.o anaevt.o -lm -L/cern/2006b/i686-slc5-gcc43-opt/lib -lpacklib -lmathlib -lgfortran -lpthread -lncurses -I/cern/pro/include/cfortran
	rm -f *.o

startup.o: startup.c startup.h anap4.h userdef.h
	$(CC) -c startup.c

histdef.o: histdef.c anap4.h userdef.h
	$(CC) -c histdef.c -I/cern/pro/include/cfortran

anaevt.o: anaevt.c anap4.h kinema.h userdef.h
	$(CC) -c anaevt.c -I/cern/pro/include/cfortran

kinelib.o: kinelib.c kinema.h
	$(CC) -c kinelib.c -I/cern/pro/include/cfortran

dataclient.o: dataclient.c dataclient.h common.h
	$(CC) -c dataclient.c -I/cern/pro/include/cfortran

clean:
	rm -f anap4 *.o



