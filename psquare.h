#ifndef p_square
#define p_square

#include <iostream>
#include <cmath>

/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////
This program will indicate whether a number is a square or not.

Input: an integer
Output: true or false 
*////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Psquare{
    public:
    bool is_square(double a);
    void prompt();
};

bool Psquare::is_square(double a){
    double temp;
    int floored;

    temp = sqrt(a);
    floored = floor(temp);
    if((temp - floored) ==0){
        //it is square
        return true;
    }
    else{
        return false;
    }
}

void Psquare::prompt(){
    double temp;

    std::cout << "Enter an integer: \n";
    std::cin >> temp;

    std::cout << Psquare::is_square(temp) << std::endl;
}

#endif