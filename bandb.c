/** 
 * Austin Van Braeckel - 1085829 - avanbrae@uoguelph.ca
 * 2020-09-17
 * 
 * A collection of various functions that manipulate data in many different ways
 */

#include "bandb.h"

/**
 * Copies byte values of the number of bytes specified by the given integer from
 * the given src address to the given unsigned char array
 */
void getbytes( unsigned char dest[], int bytes, void *src, int reverse ) {
    int i, j = 0;
    unsigned char *casted_src = (unsigned char*)src;

    if ( !reverse ) {
        for ( i = 0; i < bytes; i++ ) {
            dest[i] = casted_src[i];
        }
        dest[i] = '\0';
    } else { // reversed
        for ( i = bytes - 1; i >= 0; i-- ) {
            dest[j] = casted_src[i];
            j++;
        }
        dest[j] = '\0';
    }

}

/** 
 * Uses the given destination string to model the structure of the bits in the 
 * source data given, with '0' and '1' characters
 */
void getbits( char dest[], int bytes, void *src, int start, int end ) {
    
    int length = start - end;
    int quotient, remainder;
    int i;
    int byte_index, bit_index, start_byte_index;

    unsigned char *casted_src = (unsigned char*)src;
    
    // get quotient and remainder of the start to get byte/bit position
    quotient = start / BITS_IN_A_BYTE;
    remainder = start % BITS_IN_A_BYTE;

    start_byte_index = bytes - quotient - 1;
    byte_index = start_byte_index;
    bit_index = remainder;

    i = 0;
    while ( i < length ) {
        // go to next byte if at the end of current byte
        if ( bit_index < 0 ) {
            // reset bit position to the leftmost bit (7)
            bit_index = 7;
            byte_index++;
        }

        dest[i] = get_bit( casted_src[byte_index], bit_index);

        bit_index--;
        i++;
    }
    // set null '\0' terminator
    dest[length] = '\0';

}

/* 
 * Returns the value of the given string of bits as an unsigned
 * long long decimal number (no sign bit).
 */
unsigned long long bits2ull( char *bits ) {

    unsigned long long value = 0;
    unsigned long long addend;
    int i = 0;
    int length = strlen(bits); 

    //Loops through all characters of the source string
    while ( bits[i] != '\0' ) {

        // Adds the decimal value of the current bit to the running total if it is a '1'
        if ( bits[i] == '1' ) {
            addend = 1ULL << (length - 1 - i);
            
            // Check if overflow occurs because it is exceeding the range of unsigned long long
            if ( addend < 0 || ULLONG_MAX - value < addend ) {
                /* //Overflow occurs, but there are no handling instructions in the assignment description so no implementation is here
                fprintf(stderr, "Overflow has occured, and the number before overflowing will be returne:\t"); 
                */
            } else { // No overflow will occur, so add to running total
                value += addend;
            }
                
        } //otherwise '0' so don't add anything
        
        i++;
    }

    return value;
}

/**
 * Returns the value of the given string of bits as a signed
 * long long decimal number (with leftmost bit as sign bit).
 */
long long bits2ll( char *bits ) {

    long long value = 0;
    long long addend;
    int i = 0;
    int length = strlen(bits); 

    //Loops through all characters of the source string
    while ( bits[i] != '\0' ) {

        // Adds the decimal value of the current bit to the running total if it is a '1'
        if ( bits[i] == '1' ) {

            addend = 1LL << (length - 1 - i);
            if ( i == 0 ) { // if it is the sign bit, the value is negative
                addend *= -1LL;
            }
            
            // Check if overflow occurs because it is exceeding the range of unsigned long long
            if ( (value > 0) &&  (LLONG_MAX - value < addend) ) {
                /* //Overflow occurs, but there are no handling instructions in the assignment description so no implementation is here
                fprintf(stderr, "Overflow has occured, and the number before overflowing will be returne:\t"); 
                */
            } else { // No overflow will occur, so add to running total
                value += addend;
            }
                
        } //otherwise '0' so don't add anything
        
        i++;
    }

    return value;
}

/**
 * Retrieves the bits of the given source float, and puts them into the
 * separate categorized strings that show the binary values of the sign, exponent, and significand/mantissa
 * which represent a Single Precision IEEE 754 Binary Floating Point Standard number.
 */
void spff( char *sign, char *exponent, char *significand, float *src ) {
    char bit_string[33];
    unsigned char bytes[4];
    int i = 0;

    getbytes(bytes, 4, src, 1);
    getbits(bit_string, 4, bytes, 31, -1 );

    // Loop through the bit string and put the bits into the target strings
    while ( bit_string[i] != '\0' ) {
        
        if ( i == 0 ) { // Retrieve Sign Bit and set NULL terminator
            sign[0] = bit_string[i];
            sign[1] = '\0';
        } else if ( i < 9 ) { // Exponent - bits begin on bit_string[1], so -1 to compensate for the difference in indexes
            exponent[i-1] = bit_string[i];
            // Set NULL terminator if it is the last bit
            if ( i == 8 )
                exponent[8] = '\0';
        } else { // Significand/Mantissa - bits begin on bit_string[9], so -9 to compensate for the difference in indexes
            significand[i-9] = bit_string[i];
            // Set NULL terminator if it is the last bit
            if ( i == 31 )
                significand[23] = '\0';
        }

        i++;
    }

}

/**
 * Retrieves the bits of the given source double, and puts them into the
 * separate categorized strings that show the binary values of sign, exponent, and significand/mantissa
 * which represent a Double Precision IEEE 754 Binary Floating Point Standard number.
 */
void dpff( char *sign, char *exponent, char *significand, double *src ) {
    char bit_string[65];
    unsigned char bytes[8];
    int i = 0;

    getbytes(bytes, 8, src, 1);
    getbits(bit_string, 8, bytes, 63, -1 );

    // Loop through the bit string and put the bits into the target strings
    while ( bit_string[i] != '\0' ) {
        
        if ( i == 0 ) { // Retrieve Sign Bit and set NULL terminator
            sign[0] = bit_string[i];
            sign[1] = '\0';
        } else if ( i < 12 ) { // Exponent - bits begin on bit_string[1], so -1 to compensate for the difference in indexes
            exponent[i-1] = bit_string[i];
            // Set NULL terminator if it is the last bit
            if ( i == 11 )
                exponent[11] = '\0';
        } else { // Significand/Mantissa - bits begin on bit_string[12], so -12 to compensate for the difference in indexes
            significand[i-12] = bit_string[i];
            // Set NULL terminator if it is the last bit
            if ( i == 63 )
                significand[52] = '\0';
        }

        i++;
    }

}



/* --------------------------- HELPER FUNCTIONS - NOT FUNCTIONS PART OF A1 ASSIGNMENT DESCRIPTION --------------------------------- */

/** 
 * A simple function that returns the character of the value of the bit at the specified position (0 to 7) in the given byte.
 * It returns '0' or '1' if success, and -1 if failure.
 * Example of how the bit-numbering is implemented: 76543210 ----> The number 10010010 has a '1' in positions 7, 4, and 1 
 */
char get_bit( unsigned char byte, int bit_index ) {
    int value = 1; // 2^(0) = 1

    // error-check given bit number
    if ( bit_index > 7 || bit_index < 0 ) { /* invalid bit numbers because there are only 8 bits in a byte */
        return -1; // failure
    }

    // get value to which the source will be compared
    value = value << bit_index;

    if ( byte & value ) { // there is a '1' at that bit_index position in the given byte
        return '1';
    } else { // there is a '0' there otherwise
        return '0';
    }

 }