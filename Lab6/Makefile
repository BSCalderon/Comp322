EXECUTABLES1=spiritd moles
EXECUTABLES2=spiritd
EXECUTABLES3=moles
SRC=spiritd.c moles.c
OBJ=spiritd.o moles.o
SRC1=spiritd.c
OBJ1=spiritd.o
SRC2=moles.c
OBJ2=moles.o


CC=gcc
CFLAGS=-g


all: spiritd moles 
spiritd: spiritd.c 
	$(CC) $(CFLAGS) -c spiritd.c
	$(CC) $(CFLAGS) -o $@ spiritd.o
moles: moles.c
	$(CC) $(CFLAGS) -c moles.c
	$(CC) $(CFLAGS) -o  $@ moles.o



clean:
	rm -f $(EXECUTABLES1) $(OBJ) *~
	rm -f $(EXECUTABLES2) $(OBJ1) *~
	rm -f $(EXECUTABLES3) $(OBJ2) *~

