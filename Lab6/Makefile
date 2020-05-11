EXECUTABLES1=spiritd mole
EXECUTABLES2=spiritd
EXECUTABLES3=mole
SRC=spiritd.c mole.c
OBJ=spiritd.o mole.o
SRC1=spiritd.c
OBJ1=spiritd.o
SRC2=mole.c
OBJ2=mole.o


CC=gcc
CFLAGS=-g


all: spiritd mole 
spiritd: spiritd.c 
	$(CC) $(CFLAGS) -c spiritd.c
	$(CC) $(CFLAGS) -o $@ spiritd.o
mole: mole.c
	$(CC) $(CFLAGS) -c mole.c
	$(CC) $(CFLAGS) -o  $@ mole.o



clean:
	rm -f $(EXECUTABLES1) $(OBJ) *~
	rm -f $(EXECUTABLES2) $(OBJ1) *~
	rm -f $(EXECUTABLES3) $(OBJ2) *~

