#ifndef RSA_H
#define RSA_H\

#include <iostream>
#include <cmath>
#include <set>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "InfInt.h"
/*////////////////////////////////////////////////////////////////////////////////////////////////////////////
/This program is designed to implement the RSA cryptosystem. 
/If run as is, it will prompt the user to either request keys, or ask if they want to encrypt or decrypt messages.
/The keys given to the user will be randomly selected from a list of primes between 100 and 500.
/Through its auxiliary functions, the user may obtain all necessary parameters to execute RSA on paper. They are as follows:
/   -set_n(): modulus
/   -set_e(): public key
/   -set_m(): totient of the modulus, used to calculate d
/   -set_d(): private key 
/It should be noted that this implementation of RSA cannot deal with very large numbers. At this time, we cannot find
/a way around this. Due to this, it should not be used for any sensitive data but rather to illustrate the cryptographic 
/protocol. Additionally, when the user tries to obtain some of the relevant parameters, it is possible that the code 
/will error and issue "segmentation fault: 11"--it can be successively re-execurted until it produces a set of numbers.
/We believe this error is also occuring due to the numbers being too large to be held by long or long long.
*/////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RSA{
    public:
    int set_n();
    int prompt();
    int set_e();
    int prime_generation();
    int gcd(int a, int b);
    int encrypt(double public_key, int modulus, double plain_text);
    int n;
    int e;
    int cipher_text;
    int public_key;
    int set_m();
    int compute_d();
    int d;

    private:
    
    int decrypt(double private_key, int modulus, double cipher_text);
    int m;
    int p;
    int q;
    int plain_text;
    int private_key;
};

int RSA::prime_generation(){
    int number = 500;
    int upto = (int) floor(sqrt(500));
    int count = 0;
    int prime;
    std::set<int> full_set;
    std::set<int> primes;
    std::vector<int> composites;

    //fill set with ints 100-number
    for(int i = 100; i <= number; i++){
        full_set.insert(i);
    }
    //for n 100-number
    for(int n=100; n <= number; n++){
        //for moduli 2 to floor(sqrt(number))
        for(int j=2; j <= upto; j++){
            //check if composite, if it is, add it to the vector
            if(n % j == 0){
                composites.push_back(n);
                break;
            }
            else{
            }
        }
    }
    //Removing composite numbers from the full set
    for(std::vector<int>::const_iterator i = composites.begin(); i != composites.end(); ++i){
        full_set.erase(full_set.find(*i));
    }
    //Print out the prime list 
    //for(std::set<int>::const_iterator i = full_set.begin(); i != full_set.end(); ++i)
    //std::cout << *i << ' ';

    srand(rand() % time(NULL));
    prime = *std::next(full_set.begin(), rand() % full_set.size());
    return prime;

}

int RSA::set_n(){
    //take in two random prime numbers generate from the function "prime_generation"
    //get their product, this is n
    p = RSA::prime_generation();
    q = RSA::prime_generation();
    //primes must be distinct
    assert(p != q);
    n = p*q;
    //std::cout << n << " ";
    return n;
}

int RSA::set_m(){
    //totient function is multiplicative
    m = (p-1) * (q-1);
    //std::cout << m << " ";
    return m;
}

int RSA::gcd(int a, int b){
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

int RSA::set_e(){
    //choose a small e coprime to m
    srand(time(NULL));
    int potential_e = rand() % m; //between 0 and m-1
    int temp = RSA::gcd(potential_e, m);
    if(temp == 1 && potential_e > 1){
        e = potential_e;
        //std::cout << e << " ";
    }
    else{
        set_e();
    }
    return e;
}

int RSA::compute_d(){
    //find the multiplicative inverse of e
    //i.e. find a d st (de)%m = 1
    //any efficient e will be less than lmc(p-1, q-1)
    int lcm = ((p-1)*(q-1))/RSA::gcd(p-1, q-1);
    std::cout << lcm << " ";
    for(int i = 0; i < lcm; i++){
        if((i*e) % m == 1){
            d = i;
            //std::cout << d << " ";
        }
    }
}

int RSA::encrypt(double public_key, int modulus, double plain_text){
    //cipher = (message)^e % n
    std::cout << "public key: " << public_key << "\n";
    std::cout << "modulus: " << modulus << "\n";
    std::cout << "plaint_text: " << plain_text << "\n"; 
    cipher_text = ((long) std::pow(plain_text, public_key)) % modulus;
    std::cout << "cipher_text: " << cipher_text << "\n";
}

int RSA::decrypt(double private_key, int modulus, double cipher_text){
    //message = (cipher)^d % n 
    std::cout << "private key: " << private_key << "\n";
    std::cout << "modulus: " << modulus << "\n";
    std::cout << "cipher_text: " << cipher_text << "\n"; 
    plain_text = ((long) std::pow(cipher_text, private_key)) % modulus;
    std::cout << "plain_text: " << plain_text;
}

int RSA::prompt(){
    std::string input;
    std::string input2;
    std::string input3;
    int e;
    int n;
    int d;
    int temp_p;
    int temp_q;

    std::cout << "Y/N: Do you have a public-private key pairing or know they public key of who you are trying to communicate with?";
    std::cin >> input;
    if(input.compare("N") == 0 || input.compare("n") == 0){
        std::cout << "Y/N: Do you want a pairing?";
        std::cin >> input2;
        if(input2.compare("Y") == 0 || input2.compare("y") == 0){
            int temp_p = RSA::prime_generation();
            int temp_q = RSA::prime_generation();
            //primes must be distinct
            assert(temp_p != temp_q);
            std::cout << "Your public key is: " << temp_p << ", " << "Your private key is: " << temp_q;
        }
        else{
            std::cout << "We hope you'll consider RSA in the future.";
        }
    }
    else if(input.compare("Y") == 0 || input.compare("y") == 0){
        std::cout << "E/D: Would you like to encrpt or decrypt?";
        std::cin >> input3;

        if(input3.compare("E") == 0 || input3.compare("e") == 0){
            std::cout << "Enter the public key of the person you are trying to communicate with: ";
            std::cin >> e;
            std::cout << "Enter the modulus of the person you are trying to communicate with: ";
            std::cin >> n;
            std::cout << "Enter the message you wish to encrypt as an integer: ";
            std::cin >> plain_text;
            RSA::encrypt(e, n, plain_text);
        }
        else if(input3.compare("D") == 0 || input3.compare("d") == 0){
            std::cout << "Enter your private key: ";
            std::cin >> d;
            std::cout << "Enter your modulus: ";
            std::cin >> n;
            std::cout << "Enter the message you wish to decrypt as an integer: ";
            std::cin >> cipher_text;
            RSA::decrypt(d, n, cipher_text);
        }
        else{
            RSA::prompt();
        }
    }
    else{
        std::cout << "Invalid input.";
    }
}
#endif