#ifndef PASSGEN_H
#define PASSGEN_H


#include <random>
#include <ctime>
#include <math.h>
#include <iostream>

class PasswordGenerator{
private:
    unsigned long SEED;
    const char* ALPHAONLY = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    const char* NUMONLY = "1234567890";
    const char* SPECIALONLY = "!#$*./,";
    
    char m_Filter[100];
    int m_FilterLen = 0;


    bool FindChar(char elm, char* source, size_t len);

    char* GetFilterElements(char* filter);

public:
    PasswordGenerator();

    char* GeneratePassword(size_t length, char* filter);

    char* GeneratePassword(size_t length);

    void ApplyFilter(char* filter);


    
};


#endif