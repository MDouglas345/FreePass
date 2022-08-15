#ifndef MANAGER_H
#define MANAGER_H

#include "LexoTree.h"
#include "PassGen.h"
#include <string>

#define FILENAME "FreePass.data"

class FreePass{
private:
    PasswordGenerator   *Generator;
    LexoTree            *lTree;

    std::fstream        FileStream;


    void StoreTree();

    void ReadPassFile();

    void StoreReadPass( char* ID,  char* Pass);

    void WritePassFile();

public:
    FreePass();

    void CreatePassword(char* ID, size_t length, char* criteria);
    
    void CreatePassword(char* ID, size_t length);

    char* GetPassword(char* ID);

    bool DeletePassword(char* ID);

    void ApplyFilter(char*);
};

#endif