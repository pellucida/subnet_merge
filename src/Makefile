
OBJ=node.o tree.o netaddr.o util.o subnet_merge.o bit.o
CFLAGS=-g

all:	subnet_merge

subnet_merge:	$(OBJ)
	gcc -g -o $@ $(OBJ)

clean:	
	rm -f $(OBJ)

node.o:	node.c node.h

tree.o:	tree.c tree.h netaddr.h

netaddr.o:	netaddr.c netaddr.h

util.o:	util.c util.h

bit.o: bit.c bit.h
