/**
 * Austin Van Braeckel - 1085829 - avanbrae@uoguelph.ca
 * 2020-09-17
 * 
 * A header file containing all necessary declarations for bandb.c
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

/* function declarations from A1 Assignment description */
void getbytes( unsigned char dest[], int bytes, void *src, int reverse );
void getbits( char dest[], int bytes, void *src, int start, int end );
unsigned long long bits2ull( char *bits );
long long bits2ll( char *bits );

void spff( char *sign, char *exponent, char *significand, float *src );
void dpff( char *sign, char *exponent, char *significand, double *src );

/* helper functions and definitions */
#define BITS_IN_A_BYTE 8

char get_bit( unsigned char src, int bit_index );
