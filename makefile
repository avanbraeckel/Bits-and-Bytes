# Austin Van Braeckel - 1085829 - avanbrae@uoguelph.ca
# 2020-09-17

CC = gcc
CFLAGS = -std=c99 -Wall -pedantic

all: test_getbytes test_getbits test_bits2ull test_bits2ll test_spff test_dpff

clean:
	rm -fv *.o

bandb.o: bandb.c bandb.h
	$(CC) $(CFLAGS) -c bandb.c

test_getbytes: test_getbytes.o bandb.o
	$(CC) $(CFLAGS) -o test_getbytes test_getbytes.o bandb.o

test_getbytes.o: test_getbytes.c bandb.h
	$(CC) $(CFLAGS) -c test_getbytes.c

test_getbits: test_getbits.o bandb.o
	$(CC) $(CFLAGS) -o test_getbits test_getbits.o bandb.o

test_getbits.o: test_getbits.c bandb.h
	$(CC) $(CFLAGS) -c test_getbits.c

test_bits2ull: test_bits2ull.o bandb.o
	$(CC) $(CFLAGS) -o test_bits2ull test_bits2ull.o bandb.o

test_bits2ull.o: test_bits2ull.c bandb.h
	$(CC) $(CFLAGS) -c test_bits2ull.c

test_bits2ll: test_bits2ll.o bandb.o
	$(CC) $(CFLAGS) -o test_bits2ll test_bits2ll.o bandb.o

test_bits2ll.o: test_bits2ll.c bandb.h
	$(CC) $(CFLAGS) -c test_bits2ll.c

test_spff: test_spff.o bandb.o
	$(CC) $(CFLAGS) -o test_spff test_spff.o bandb.o

test_spff.o: test_spff.c bandb.h
	$(CC) $(CFLAGS) -c test_spff.c

test_dpff: test_dpff.o bandb.o
	$(CC) $(CFLAGS) -o test_dpff test_dpff.o bandb.o

test_dpff.o: test_dpff.c bandb.h
	$(CC) $(CFLAGS) -c test_dpff.c