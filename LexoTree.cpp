#include "LexoTree.h"


bool LexoTree::SetWord(char* word, char* pass){
    size_t len = strlen(word);
    char* current = word;

    LexoNode* CurrentNode = Root;

    for (int i = 0; i < len; i++){
        size_t index = (size_t)(*(current + i));
        

        LexoNode* child = &(CurrentNode->Children[index]);

        if (!child){
            CurrentNode->initMem();
            child = &(CurrentNode->Children[index]);
        }
        
        CurrentNode = child;
    }

    CurrentNode->end = true;
    CurrentNode->Password = pass;
    return true;
}

char* LexoTree::GetPass(char* word){
   
    size_t len = strlen(word);
    LexoNode* CurrentNode = Root;

    

    for (size_t i = 0; i < len; i++){
        size_t index = (int)*(word + i);

        LexoNode* t = &(CurrentNode->Children[index]);
        
        if (!t){return nullptr;}

        CurrentNode = t;
    }

    return CurrentNode->Password;
}

void LexoTree::DumpNode(LexoNode* node, char id){
    if (!node){
        return;
    }

    std::cout << id << " ";

    for (int i = 0; i < 255; i++){
        DumpNode(&(node->Children[i]), char(i));
    }

}

void LexoTree::DumpNode2(std::ostream& stream, LexoNode* node, int lvl){
    if (lvl > 99){return;}
    if (node->end){
        DumpText[lvl] = '\0';
        stream << DumpText << "\n";
        stream << node->Password << "\n";
    }
    if (!node->Children){return;}

    for (int i = 0; i < 255; i++){
        DumpText[lvl] = (char)i;
        DumpNode2(stream, &(node->Children[i]), lvl + 1);
    }
}



void LexoTree::DumpTree(std::ostream& stream){
    DumpNode2(stream, Root, 0);
}