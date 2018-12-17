#include "gcd.h"

int main() {
    GCD GCDobj;

    GCDobj.prompt();

    std::cout << GCDobj.compute(12,4) << std::endl;

    return 0;
}

