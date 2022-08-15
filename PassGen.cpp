#include "PassGen.h"


PasswordGenerator::PasswordGenerator(){
    std::time_t now = time(0);
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

char* PasswordGenerator::GeneratePassword(size_t length, char* filter){
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

    return GENPASSWORD;
}


bool PasswordGenerator::FindChar(char elm, char* source, size_t len){
    for (size_t i = 0; i < len; i++){
        if (elm == *(source + i)){return true;}
    }
    return false;
}

char* PasswordGenerator::GetFilterElements(char* filter){
    char *Result = (char*)malloc(sizeof(char) * 3);
    char* current = filter;
    size_t i = 0;
    size_t len = strlen(filter);

    for (size_t i = 0; i < len; i++){
        std::cout << current << "\n";
        if (*current != '|'){
            *(Result + i) = *current;
        }    
        current++;
    }
  
    return Result;
}

void PasswordGenerator::ApplyFilter(char* filter){
    char* filterElements = GetFilterElements(filter);

     std::cout << filterElements << "\n";

   /* while (filterElements){
        switch(*filterElements){
            case 'A': 
                std::cout << "Alpha only\n";
                break;
            case '!':
                std::cout << "Special only\n";
                break;
            case '0':
                std::cout << "Numeral only\n";
                break;
            default:
                std::cout << "Invalid filter\n";
                break;
        }
        filterElements++;
    }
    */
}