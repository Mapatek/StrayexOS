/*
 Strayex Kernel C Library "klib"
 v1.0.1
 Kernel Standard Library file, access through "kstdlib.h"
 Copyright 2019 Daniel Strayker Nowak
 All rights reserved
 
 Code added to file from:
 https://www.geeksforgeeks.org/implement-itoa/
 https://stackoverflow.com/questions/3835922/simple-swap-function-why-doesnt-this-one-swap
*/

#include <stdbool.h>
#include "kstdlib.h"
#include "kstring.h"

// Reading from I/O ports:
unsigned char kinportb (unsigned short _port)
{
	unsigned char rv;
	__asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
	return rv;
}

// Writting from I/O ports:
void koutportb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

// Swapping integers in memory:
void kswap(int* a, int* b)
{
 int temp = *a;
 *a = *b;
 *b = temp;
}

// Reversing strings:
void kreverse(char str[])
{
    int start = 0;
	int length = kstrlen((unsigned char *)str);
    int end = length -1;
    while (start < end)
    {
        kswap((int *)(str+start), (int *)(str+end));
        start++;
        end--;
    }
}

// Converting integer to char table:
char *kitoa(int value, char *str, int base)
{
    char * rc;
    char * ptr;
    char * low;
    // Check for supported base.
    if ( base < 2 || base > 36 )
    {
        *str = '\0';
        return str;
    }
    rc = ptr = str;
    // Set '-' for negative decimals.
    if ( value < 0 && base == 10 )
    {
        *ptr++ = '-';
    }
    // Remember where the numbers start.
    low = ptr;
    // The actual conversion.
    do
    {
        // Modulo is negative for negative value. This trick makes abs() unnecessary.
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + value % base];
        value /= base;
    } while ( value );
    // Terminating the string.
    *ptr-- = '\0';
    // Invert the numbers.
    while ( low < ptr )
    {
        char tmp = *low;
        *low++ = *ptr;
        *ptr-- = tmp;
    }
    return rc;
}

// Interrupt management:

// Enable interrupts:
void Int_on()
{
	asm("sti");
}

// Disable interrupts:
void Int_off()
{
	asm("cli");
}
