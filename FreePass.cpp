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

    1. Initalize Seed for RAND

    2. Create a filter for which character sets to use when generating password

    3. Generate password given a desired length

    4. Create a data structure that stores the password and some identifer for which this password is used for.

    5. Store them in an external file, which can be queried


    Appendum 3 :
    Slight oversight on prime number generation. To make life just a little bit easier at the cost of security(? maybe it affects it ?), we will take the master password
    break it into two unique chunks and cast them as integers so that they are the input for RSA key generation.


    References : 
    RSA implementation https://en.wikipedia.org/wiki/RSA_(cryptosystem)
    C++ RAND https://en.cppreference.com/w/cpp/numeric/random/rand


*/

#include <iostream>
#include <random>
#include <ctime>
#include <string.h>
#include <fstream>

using namespace std;

bool SETUP = false;



char* PASSWORDDUMP;

char* MASTERPASSWORD;

char ALPHAONLY[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"};
char NUMONLY[] = {"1234567890"};
char SPECIALONLY[] = {"!#$*./,"};


struct STOREDPASSWORD{
    size_t length;
    char Name[100];

};


bool FindChar(char elm, char* source, size_t len){
    for (size_t i = 0; i < len; i++){
        if (elm == *(source + i)){return true;}
    }
    return false;
}

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

char* GeneratePassword(size_t length, char* filter){
    char* GENPASSWORD = (char*)malloc(length);

    //min + rand() % (( max + 1 ) - min);
    int filterlen = strlen(filter);
    for (int i = 0; i < length; i++){
        char c = (char)(32 + rand() % ((127 +1) - 32));
        while(!FindChar(c, filter, filterlen)){
            c = (char)(32 + rand() % ((127 +1) - 32));
        }
        GENPASSWORD[i] = c;
    }
    std::cout << GENPASSWORD << "\n";
    std::cout << '\n';

    return GENPASSWORD;
}


void RSA_TEST(char* source){
    size_t len = strlen(source);

    char* LeftHalf = (char*)malloc(len/2-1);
    char* RightHalf = (char*)malloc(len/2);

    for (int i = 0; i <= len/2 ; i++){
        LeftHalf[i] = source[i];
        RightHalf[i] = source[i + (len/2) ];

        cout << LeftHalf << " " << RightHalf << "\n"; 
    }
    
}

int main(int argc, char* argv[]){
    RSA_TEST("MaryHadALittleLamb");
    initalizeSeed();



    char filter[100];
    strcat(filter, ALPHAONLY);

    strcat(filter, NUMONLY);
  
    strcat(filter, SPECIALONLY);
  


    for (int i = 0; i < 25; i++){
        GeneratePassword(15, filter);
    }
}