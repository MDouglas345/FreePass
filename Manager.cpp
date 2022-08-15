#include "Manager.h"

FreePass::FreePass(){
    Generator = new PasswordGenerator();
    lTree = new LexoTree();
    //FileStream.open("FreePass.data", std::fstream::in | std::fstream::out);

    ReadPassFile();
}

void FreePass::CreatePassword(char* ID, size_t length, char* criteria){
    char* pass = Generator->GeneratePassword(length, criteria);
    
    std::cout << "Created password : " << pass << "\n";
    
    lTree->SetWord(ID, pass);
}

char* FreePass::GetPassword(char* ID){
    return lTree->GetPass(ID);
}

void FreePass::StoreReadPass(char* ID, char* Pass){
    lTree->SetWord(ID, Pass);
}

void FreePass::ReadPassFile(){
    FileStream.open(FILENAME, std::fstream::in);
    if (FileStream.fail()){
        std::cout << "New installation detected!\n"; 
        FileStream.close(); 
        FileStream.open(FILENAME, std::fstream::out); 
        FileStream.close(); 
        FileStream.open(FILENAME, std::fstream::in);
        }

    std::string line;

    while (std::getline(FileStream, line)){
        std::string pass;
        std::getline(FileStream, pass);
        StoreReadPass(&line[0], &pass[0]);
    }


}

void FreePass::ApplyFilter(char* filter){
    Generator->ApplyFilter(filter);
}

