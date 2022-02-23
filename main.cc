#include "fileio.h"
#include <cstdio>

int main(){
    FileIO fio;
    if(fio.Open("main.cc",FILE_READ)){
        int file_size = fio.GetFileSize();
        char *buffer = nullptr; 
        buffer = (char *)malloc(file_size+1);
        if(!buffer){
            printf("Allocation failed\n");
            return -1;
        }
        fio.Read(buffer,file_size);
        buffer[file_size] = '\0';
        printf("File opening success\n");
        printf("File size: %d\n\n", file_size);
        printf("File Contents: \n%s\n",buffer);
        free(buffer);
        fio.Close();
    }else{
        printf("File opening failed\n");
    }
    return 0;
}