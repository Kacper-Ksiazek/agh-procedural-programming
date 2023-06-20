#include "stdio.h"
#include <stdarg.h>

#include "printf.h"

void outNum(int x) {
    if (x > 0) {
        outNum(x / 10);
        outDec(x % 10);
    }
}

void outChar(char c) {
    putchar(c);
}

void outStr(const char *string) {
    while (*string != '\0') {
        outChar(*string++);
    }
}

void outDouble(double x) {
    if (x == 0) return outChar('0');

    if (x < 0) {
        outChar('-');
        x *= -1;
    };

    int integerPart = (int) x;
    double fractionPart = x - integerPart;
    // Print integer part of the number

    // We have to manually check if integer part is equal to 0, because due to the recursive architecture
    // of number printing function, leading 0 cannot be displayed in a common way.
    if (integerPart == 0) outDec(0);
    else outNum(integerPart);

    // Check whether there is fraction at all
    if (fractionPart == 0) return;

    // Begin fraction printing with a dot
    outChar('.');

    // Multiply fraction part by 10 as long as there is remaining fraction part
    // There can be only up to 6 digits after dot by default while printing variable type of double
    // using printf
    while (((int) (fractionPart) - fractionPart) != 0 && fractionPart < 1e+5) {
        fractionPart *= 10;
    }
    // Round the fraction one up if it's necessary
    if ((int) (fractionPart * 10) % 10 >= 5) fractionPart += 1;

    // Print fraction part
    outNum((int) fractionPart);
}

void outDec(int x) {
    outChar(x + '0');
}

int Printf(const char *sFormat, ...) {
    va_list args;
    va_start(args, sFormat);
    int res = PrintfV(sFormat, args);
    va_end(args);

    return res;
}

int PrintfV(const char *sFormat, va_list va_args) {
    char c;

    while((c= *sFormat++)){
        switch (c) {
            // Handle variable injection
            case ('%'):
                // Read next character in order to discover what kind of variable ought to be injected
                switch ((c = *sFormat++)) {
                    // %d- Inject integer
                    case ('d'):
                        outNum(va_arg(va_args, int));
                        break;

                    // %c- Inject character
                    case ('c'):
                        // This should do: "outChar(va_arg(va_args,char));"
                        // But my IDE does not allow me to do so, so gotta improvise
                        outChar((char)va_arg(va_args,int));
                        break;

                    // %s- Inject string
                    case ('s'):
                        outStr(va_arg(va_args,const char *));
                        break;

                    // %f- Inject double
                    case ('f'):
                        outDouble(va_arg(va_args,double));
                        break;


                    // Otherwise we have to assume, that it's ony percent char & there is no variable to be injected
                    default:
                        // Display standalone % sign
                        outChar('%');

                        // Instead of tackling character which occurs right after % here,
                        // it's more convenient to go back
                        *sFormat--;
                        break;

                }
                break;

            // Handle transformation ` into '
            case ('`'):
                outChar('\'');
                break;

            // Handle displaying anything other
            default:
                outChar(c);
                break;
        }
    }

    return 1;
}