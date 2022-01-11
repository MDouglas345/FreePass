/*
    A bare minimum attempt at making a secure password encryptor and manager. Forced to do so because passwords are a pain and do not particularly feel like spending money

    There are two parts to this problem. There is the generation part and there is the password storage part.

    The generation part of the problem revolves around implementing some algorithm that can generate long, secure passworsds; this would preferably be based on some constant (maybe the main password that the user must rememeber?)

    The password storage part of this problem revolves around storing these generated password in such a way that no one can simply just open the .dat file and be able to see these passwords.
    I already have a solution in mind for this, the RSA public key encryption algorithm.

    The problem is finding a solution for the first.

    Appendum 1 : 

    Perhaps using the std Random function to generate each password? The seed being the name of said the time at which the program was started! Important.
    
    Appendum 2 :
    The random function is inadequate. The dont even really look like passwords! Needs more tuning and modification

    PROGRAM FLOW :

    Initalize Seed for RAND



    References : 
    RSA implementation https://en.wikipedia.org/wiki/RSA_(cryptosystem)
    C++ RAND https://en.cppreference.com/w/cpp/numeric/random/rand


*/

#include <iostream>
#include <random>
#include <ctime>
#include <string.h>

using namespace std;


char* PASSWORDDUMP;

char* ALPHNUMONLY = {"abcdefghijklmnopqrstuvwxyz"};

void initalizeSeed(){
    time_t now = time(0);
    char* date_time = ctime(&now);
    int leng = strlen(date_time);

    char* current = date_time;
   

    unsigned long SEED = 0;

    for ( int i = 0; i < leng; i++){
        SEED += (unsigned long)(*current);
        current++;
    }



    srand(SEED);
}

char* GeneratePassword(size_t length){

    //min + rand() % (( max + 1 ) - min);
    for (int i = 0; i < length; i++){
        cout << (char)(32 + rand() % ((127 +1) - 32)) << " " ;
    }
    std::cout << '\n';

}


int main(int argc, char* argv[]){
    std::cout << "Hello World\n";
    initalizeSeed();
    cout << "ALL CHAR VALUES FROM 33 - 127\n";

    for (int i = 32; i < 127; i++){
        cout << i << " " <<(char)i << '\n';
         
    }

    for (int i = 0; i < 25; i++){
        GeneratePassword(100);
    }
}