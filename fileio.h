#ifndef FILEIO_H
#define FILEIO_H

#include<cstdlib>

#define FILE_READ   0x1
#define FILE_WRITE  0x2
#define FILE_APPEND 0x4
#define FILE_CREAT  0x8
#define FILE_EXCL   0x10

#define FILE_SEEK_SET 0x1
#define FILE_SEEK_CUR 0x2
#define FILE_SEEK_END 0x3

class FileIO {
private:
    int m_fileptr;
public:
    FileIO();
    
    int Open(const char *file_name,int perm);
    int Read(void *buffer,std::size_t bytes_to_read);
    int Write(void *buffer,std::size_t bytes_to_write);
    int sync();
    int GetFileSize();
    long int Seek(long int offset,int whence);
    long int SeekTell();
    int Close();
};

#endif