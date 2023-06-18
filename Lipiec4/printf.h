#pragma once

#include "stdarg.h"

/**
 * Simplified version of printf function
 *
 * @param sFormat message format
 * @param ...  variable number of arguments satisfying given format
 * @return 0 if no error has occured and 1 otherwise
 */
int Printf(const char *sFormat, ...);


/**
 * Simplified version of printf function with organized
 *
 * @param sFormat message format
 * @param va_arg organized list of received arguments
 * @return 0 if no error has occured and 1 otherwise
 */
int PrintfV(const char *sFormat, va_list va_arg);

/**
 * Print decimal
 *
 * @param x decimal to be printed
 */
void outDec( int x);


/**
 * Print single character
 *
 * @param c character to be printed
 */
void outChar( char c);


/**
 * Print string
 *
 * @param string string to be printed
 */
void outStr( char* string );


/**
 * Print variable type of double
 *
 * @param x double to be printed
 */
void outDouble( double x);


/**
 * Recursively print an integer greater than 0
 *
 * @param x remaining integer to be printed
 */
void outNum( unsigned int x );