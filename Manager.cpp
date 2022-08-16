#include "Manager.h"

FreePass::FreePass(){
    Generator = new PasswordGenerator();
    lTree = new LexoTree();
    //FileStream.open("FreePass.data", std::fstream::in | std::fstream::out);

    ReadPassFile();
}

void FreePass::CreatePassword(char* ID, size_t length){
    char* pass = Generator->GeneratePassword(length);
    
    std::cout << "Created password : " << pass << "\n";
    
    lTree->SetWord(ID, pass);

    /**
     * need to write new entries to file
     * 
     */
     

     WritePassFile();
}

void FreePass::CreatePassword(char* ID, size_t length, char* criteria){
    char* pass = Generator->GeneratePassword(length, criteria);
    
    std::cout << "Created password : " << pass << "\n";

   

    lTree->SetWord(ID, pass);

    WritePassFile();
}

char* FreePass::GetPassword(char* ID){
    return lTree->GetPass(ID);
}

void FreePass::StoreReadPass(char* ID, char* Pass){
    char* newID = (char*)malloc(sizeof(char) * strlen(ID));
    char* newPass = (char*)malloc(sizeof(char) * strlen(Pass));

    strcpy(newID, ID);
    strcpy(newPass, Pass);
    lTree->SetWord(newID, newPass);
    //std::cout << ID << " " << Pass << "\n";
}

void FreePass::WritePassFile(){
    FileStream.open(FILENAME, std::fstream::out);

    if (FileStream.fail()){
        std::cout << "Failed to open file to write passwords!";
        return;
    }

    /**
     * @brief 
     * Some kind of encryption algorithm goes here
     * For now, just write the damn file.
     */

    lTree->DumpTree(FileStream);
    FileStream.close();
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
        //std::cout << "Read " << line << " " << pass << "\n";
        StoreReadPass(&line[0], &pass[0]);
    }

    FileStream.close();

}

void FreePass::ApplyFilter(char* filter){
    Generator->ApplyFilter(filter);
}

