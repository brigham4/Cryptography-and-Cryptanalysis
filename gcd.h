#ifndef GCD_H
#define GCD_H

#include <iostream>
#include <cmath>
  
/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////
This program to executes the Euclidean algorithm on two numbers and returns their GCD. 
When run, the program will ask the user to present two integers.

Input: two integers: a,b
Output: GCD(a,b)
*////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class GCD{
    public:
    int compute(int a, int b);
    int prompt();
};

int GCD::compute(int a, int b){
    int previous_residual;
    int residual;
    int gcd;
    int quotient;

    if(a == b){
        gcd = a;
        return gcd;
    }

    if(a > b){
        while(residual != 0){
            quotient = floor(a/b);
            previous_residual = residual;
            residual = a - (quotient*b);
            if(residual == 0){
                //if b is a divisor of a, then b is their GCD
                gcd = b;
                break;
            }
            gcd=previous_residual;
            b = a;
            a = residual;
        }
        return gcd;
    }
    else{
        while(residual != 0){
            quotient = floor(b/a);
            previous_residual = residual;
            residual = b-(quotient*a);
            if(residual == 0){
                //if a is a divisor of b then a is their GCD
                gcd = a;
                break;
            }
            gcd=previous_residual;
            b = a;
            a = residual;
        }
        return gcd;
    }
}  

int GCD::prompt(){
    int a = 0;
    int b = 0;
    
    std::cout << "Enter the first integer: \n";
    std::cin >> a;

    std::cout << "Enter second integer: \n";
    std::cin >> b;

    std::cout << GCD::compute(a,b) << std::endl;
    return GCD::compute(a,b);
    
}


#endif
