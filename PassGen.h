#ifndef PASSGEN_H
#define PASSGEN_H


#include <random>
#include <ctime>
#include <math.h>
#include <iostream>

class PasswordGenerator{
private:
    unsigned long SEED;
    char m_Filter[100];

    bool FindChar(char elm, char* source, size_t len);

    char* GetFilterElements(char* filter);

public:
    PasswordGenerator();

    char* GeneratePassword(size_t length, char* filter);

    void ApplyFilter(char* filter);


    
};


#endif