#ifndef diophantine_H
#define diophantine_H

#include <iostream>
#include <cmath>

/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////
This program will find the solution of a diophantine equation, should one exist. If a soltiuon does not exist
however, the user will be informed as such. 

Input: three integers a,b,c
Output: true if there is a solution, false if there isn't
*////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Diophantine{
    public:
     bool solve(int a, int b, int c);
     void prompt();
};

bool Diophantine::solve(int a, int b, int c){
    int sum = c;

    GCD GCDinst;
    int gcd_ab = GCDinst.compute(a,b);

    if(c % GCDinst.compute(a,b) == 0){
        //There exists a solution
        return true;
    }
    else{
        //There does not exist a solution
        return false;
    }
}

void Diophantine::prompt(){
    int a;
    int b;
    int c;

    std::cout << "Enter first coefficient: \n";
    std::cin >> a;

    std::cout << "Enter second coefficient: \n";
    std::cin >> b;

    std::cout << "Enter their sum: \n";
    std::cin >> c;

    std::cout << Diophantine::solve(a,b,c) << std::endl;
}

#endif