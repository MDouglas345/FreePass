#include <iostream>
#include <random>
#include <ctime>
#include <string.h>
#include <fstream>
#include <math.h>

struct LexoNode{
    LexoNode *Children;
    bool end;
    char* Password;

    LexoNode(){
        Children = (LexoNode*)malloc(sizeof(LexoNode)* 255);
    }

    void initMem(){
         Children = (LexoNode*)malloc(sizeof(LexoNode)* 255);
    }
    
};

class LexoTree{
private:
    size_t TotalNodes;
    LexoNode* Root;

public:
    LexoTree(){
        Root = new LexoNode();
    }

    bool SetWord(char* word, char* pass);

    char* GetPass(char* word);

    void DumpNode(LexoNode* , char );

    void DumpTree();
};