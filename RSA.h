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
/   -set_modulus(): modulus
/   -set_public_key(): public key
/   -set_m(): totient of the modulus, used to calculate d
/   -set_private_key(): private key 
/It should be noted that this implementation of RSA cannot deal with very large numbers. At this time, we cannot find
/a way around this. Due to this, it should not be used for any sensitive data but rather to illustrate the cryptographic 
/protocol. Additionally, when the user tries to obtain some of the relevant parameters, it is possible that the code 
/will error and issue "segmentation fault: 11"--it can be successively re-executed until it produces a set of numbers.
/We believe this error is also occuring due to the numbers being too large to be held by long or long long.

/If you would like to try encrypting a message, try the following parameters:
/public key: 5
/modulus: 133
/message: 10
/the program should print out the cipher text: 117
*/////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RSA{
    public:
    int set_modulus();
    int prompt();
    int set_public_key();
    int prime_generation();
    int gcd(int a, int b);
    int encrypt(double public_key, int modulus, double plain_text);
    int set_m();
    int set_private_key();
    int modulus;
    int public_key;
    int cipher_text;
    
    private:
    int decrypt(double private_key, int modulus, double cipher_text);
    int p;
    int q;
    int m;
    int plain_text;
    int private_key;
};

int RSA::prime_generation(){
    int number = 250;
    int upto = (int) floor(sqrt(number));
    int count = 0;
    int prime;
    std::set<int> full_set;
    std::vector<int> composites;

    for(int i = 100; i <= number; i++){
        full_set.insert(i);
    }
    for(int n=100; n <= number; n++){
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

    srand(rand() % time(NULL));
    //We can't access sets by index so we need to use std::next which returns an iterator pointing to the element
    //that it(the iterator) would be pointing to if advanced n (here a random amount) positions. 
    prime = *std::next(full_set.begin(), rand() % full_set.size());
    std::cout << prime << " ";
    return prime;
}

int RSA::set_modulus(){
    //call the function "prime_generation" to obtain two prime numbers
    //get their product, this is the modulus
    p = RSA::prime_generation();
    q = RSA::prime_generation();
    //primes must be distinct--if not, reselect
    while(p == q){
        p = RSA::prime_generation();
        q = RSA::prime_generation();
    }
    if(p != q){
        modulus = p*q;
        std::cout << "modulus: " << modulus << "\n";
        return modulus;
    }
}

int RSA::set_m(){
    //m will be used later to compute the public and private keys, it is the totient of the modulus.
    //totient function is multiplicative so we can use the following property:
    m = (p-1) * (q-1);
    std::cout << "m: "<< m << "\n";
    return m;
}

int RSA::gcd(int a, int b){
    int gcd;
    if(b == 0){
        gcd = a;
        return gcd;
    }
    else{
        gcd = RSA::gcd(b, a % b);
        return gcd;
    }
}  

int RSA::set_public_key(){
    //choose a small e (public_key) coprime to m
    srand(time(NULL));
    int potential_public_key = rand() % m; 
    int temp = RSA::gcd(potential_public_key, m);
    if(temp == 1 && potential_public_key > 1){
        public_key = potential_public_key;
        //std::cout << public_key << " ";
    }
    else{
        set_public_key();
    }
    return public_key;
}

int RSA::set_private_key(){
    //find the multiplicative inverse of public_key
    //i.e. find a d st (de)%m = 1
    //The implementation where we bound i by the LCM has some problems, these (I think) are due to the public key being made too large.
    //any efficient private key will be less than lcm(p-1, q-1)
    //note lcm(p-1, q-1) = (p-1)(q-1)/gcd(p-1, q-1) = m/gcd(p-1, q-1)
    //int lcm = (m)/RSA::gcd(p-1, q-1);
    for(int i = 0; i < modulus; i++){
        if((i*public_key) % m == 1){
            private_key = i;
            //std::cout << "private_key:" << private_key << " ";
            return private_key;
            break;
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
    return cipher_text;
}

int RSA::decrypt(double private_key, int modulus, double cipher_text){
    //message = (cipher)^d % n 
    std::cout << "private key: " << private_key << "\n";
    std::cout << "modulus: " << modulus << "\n";
    std::cout << "cipher_text: " << cipher_text << "\n"; 
    plain_text = ((long) std::pow(cipher_text, private_key)) % modulus;
    std::cout << "plain_text: " << plain_text;
    return plain_text;
}

int RSA::prompt(){
    std::string input;
    std::string input2;
    std::string input3;
    int input_public_key;
    int input_modulus;
    int input_private_key;

    std::cout << "Y/N: Do you have a public-private key pairing or know they public key of who you are trying to communicate with?";
    std::cin >> input;
    if(input.compare("N") == 0 || input.compare("n") == 0){
        std::cout << "Y/N: Do you want a pairing?";
        std::cin >> input2;
        if(input2.compare("Y") == 0 || input2.compare("y") == 0){
            RSA::set_modulus();
            RSA::set_m();
            RSA::set_public_key();
            RSA::set_private_key();
            std::cout << "Your public key is: " << public_key << "\n" << "Your private key is: " << private_key << "\n" << "Your modulus is: " << modulus << "\n";
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
            std::cin >> input_public_key;
            std::cout << "Enter the modulus of the person you are trying to communicate with: ";
            std::cin >> input_modulus;
            std::cout << "Enter the message you wish to encrypt as an integer: ";
            std::cin >> plain_text;
            RSA::encrypt(input_public_key, input_modulus, plain_text);
        }
        else if(input3.compare("D") == 0 || input3.compare("d") == 0){
            std::cout << "Enter your private key: ";
            std::cin >> input_private_key;
            std::cout << "Enter your modulus: ";
            std::cin >> input_modulus;
            std::cout << "Enter the message you wish to decrypt as an integer: ";
            std::cin >> cipher_text;
            RSA::decrypt(input_private_key, input_modulus, cipher_text);
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