#include "printf.h"

int main() {
    int n  = -0;
    char c = '$';
    double x = 12000000.34050000012;
    double y = -.12;
    double z = -0.5;
    char*  str = (char*)"to jest string";

    Printf( "%s\n%f%c  n=%d \\ % /\ny=%f ` ` z=%f\n\n", str, x, c, n, y, z );
    return 0;
}
