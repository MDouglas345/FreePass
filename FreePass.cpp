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

    Appendum 4 :
    Taking a break from the encryption aspect. Focused on a working product.
    Working on a LexoTree. which is inspiration from one of Tsoding videos. A tree that keeps track fo all possible characters and makes out words. Used for autocompletion / suggestion

    Appendum 5 :
    Implemented Lexotree. Now I need a way of traversing the tree and obtaining all stored data in it. Might be a challenge.
    Limit word to 100 chars.

    Appendum 6 :
    Looking into creating an interface. The idea of a session so that the user does not have to enter a password each time they want to do something is appealing.


    References : 
    RSA implementation https://en.wikipedia.org/wiki/RSA_(cryptosystem)
    C++ RAND https://en.cppreference.com/w/cpp/numeric/random/rand
    GCD https://en.wikipedia.org/wiki/Euclidean_algorithm#Implementations



*/

#include "Manager.h"

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

void DumpDebug(char* memory, size_t len){
    char* current = memory;
    for (int i = 0; i < len; i++){
        cout << (size_t)(*current) << " ";
        current++;
    }
    cout << "\n";
}

int GCD(int a, int b){
    if (b == 0){
        return a;
    }
    else{
        return GCD(b, a % b);
    }
}


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
    for (int i = 0; i < length-1; i++){
        char c = (char)(32 + rand() % ((127 +1) - 32));
        while(!FindChar(c, filter, filterlen)){
            c = (char)(32 + rand() % ((127 +1) - 32));
        }
        GENPASSWORD[i] = c;
    }

    GENPASSWORD[length] = '\0';

    std::cout << GENPASSWORD << "\n";
    std::cout << '\n';

    return GENPASSWORD;
}

size_t GetNumFromString(char* source){
    char* current = source;
    size_t res = 0;
    while (*current != '\0'){
        res += (size_t)(*current);
        current++;
    }

    return res;
}

char* Encrypt(size_t PublicKey, size_t N, char* Message){
    char* current = Message;
    char* EncryptedMessage = (char*)malloc(strlen(Message));
    size_t i = 0;
    while (*current != '\0'){
        cout << (size_t)(*current) << " ";
        EncryptedMessage[i] =  (char)std::pow((size_t)(*current), PublicKey) % N;
        current++;
        i++;
    }
    cout << "\n";

    return EncryptedMessage;
}

char* Encrypt2(size_t PublicKey, size_t N, char* Message){
    int* current = reinterpret_cast<int*>(Message);
    char* EncryptedMessage = (char*)malloc(strlen(Message));
    int* EnMess = reinterpret_cast<int*>(EncryptedMessage);

    while (current){
        (*EnMess) = (int)std::pow((*current), PublicKey) % N;
        EnMess++;
        current++;
    }

    return EncryptedMessage;

}

char* Decrypt(size_t PrivateKey, size_t N, char* Message){
    char* current = Message;
    char* DecryptedMessage = (char*)malloc(strlen(Message));
    size_t i = 0;

    while (*current != '\0'){
        DecryptedMessage[i] =  (char)std::pow((size_t)(*current), PrivateKey) % N;
        current++;
        i++;
    }

    return DecryptedMessage;
}

void RSA_TEST(char* source){

    //BREAK THE STRING IN 2!
    size_t len = strlen(source);
    size_t halflen = std::ceil((double)len/2);
    cout << "Password length : " << len << " \n";
    cout << "Half length : " << halflen << " \n";

    char* LeftHalf = (char*)malloc(halflen);
    char* RightHalf = (char*)malloc(halflen);

    for (int i = 0; i <= halflen ; i++){
        LeftHalf[i] = source[i];
        RightHalf[i] = source[i + (len/2)];

    }

    //Not sure if this part is necerssary? Better safe than sorry.
    LeftHalf[len/2] = '\0';
    RightHalf[len] = '\0';


    //INTERPRET THEM AS INTEGERS! P AND Q
    size_t P = GetNumFromString(LeftHalf);
    size_t Q = GetNumFromString(RightHalf);
    std::cout << " P AND Q : " << P << " " << Q << "\n";

    //CALCULATE N = PQ
    size_t N = P * Q;
    std::cout << "N : " << N << " \n";

    //CALCULATE Np = (P-1)(Q-1)
    size_t Np = (P-1) * (Q-1);
    std::cout << "Np : " << Np << "\n";

    //Find some value e that is relatively prime ( USE GCD == 1) and that is the public key.
    size_t PublicKey = rand();
    while(GCD(PublicKey, Np) != 1){
        PublicKey = rand();
    }
    cout << "The public key is " << PublicKey << " \n";

    //Find d = e^-1 MOD Nq. This is the private key.
    //FIX THIS! THIS IS CAUSING ISSUES!///////////////////////////////////
    size_t PrivateKey = (Np * rand()) + 1;
    
    cout << "The private key is " << PrivateKey << "\n";

    //TEST THE ENCRYPTION!
    char MESSAGE[] = {"HelloWorld!"};
    char* EN = Encrypt(PublicKey, N, MESSAGE);
    char* DE = Decrypt(PrivateKey, N, EN);

    std::cout << "Message to encrypt : " << MESSAGE << " \n";
    std::cout << "Encrypted : " ;
    DumpDebug(EN, 10);
    cout << "\n";
    std::cout << "Decrypted : ";
    DumpDebug(DE, 10);
    cout << "\n";


    //cout << LeftHalf << " " << RightHalf << "\n";
    
}

void RetrieveFromFile(){

}

void Usage(){
    std::cout << "USAGE :   FreePass <command>  <optionals>\n";
    std::cout << "                    np        <NameOfPassword>        <length>        <criteria>      //Create a new password\n";
    std::cout << "                                                                      A               //Alphabet only\n";
    std::cout << "                                                                      0               //Numerals only\n";
    std::cout << "                                                                      !               //Specials only\n";
    std::cout << "                                                                      A|0|!           //Combination\n";
    std::cout << "                    gp        <NameOfPassword>                                        //Get password\n";
    std::cout << "                    dp        <NameOfPassword>                                        //Delete Password\n";
    
}


void LEXOTREE_TEST(){
    LexoTree Tree;

    char Word[]  = {"HelloWorld"};
    char Word2[] = {"Hello"};
    char Word3[] = {"Helium"};
    char Pass[] = {"ThisIsASecret"};
    char Pass2[] = {"ThisIsAnotherSecret"};
    char Pass3[] = {"WhatAWonderfulWorld"};

    Tree.SetWord(Word,Pass);
    Tree.SetWord(Word2, Pass2);
    Tree.SetWord(Word3, Pass3);

    //std::cout << Tree.GetPass(Word) << "\n";
    //std::cout << Tree.GetPass(Word2) << "\n";

    Tree.DumpTree(std::cout);
}

int main(int argc, char* argv[]){ 

    FreePass PassManager;

    if (argc < 2){Usage(); return 1;}

    if (strcmp(argv[1], "np") == 0){
        if (argc < 5){Usage(); std::cout << "Not enough arguements\n";return 1;}
        PassManager.ApplyFilter(argv[4]);
        std::cout << "Creating new password...\n";

        }
    else if (strcmp(argv[1], "gp") == 0){std::cout << "Getting password...\n";}
    else if (strcmp(argv[1], "dp") == 0){std::cout << "Deleting password...\n";}
    else{Usage(); return 1;}
    
    

/*
    // LEXOTREE_TEST();

   // RSA_TEST("MichaelLeonardoDouglas");


    char filter[100];
    strcat(filter, ALPHAONLY);

    strcat(filter, NUMONLY);
  
    strcat(filter, SPECIALONLY);



    for (int i = 0; i < 25; i++){
        GeneratePassword(15, filter);
    }
*/
}