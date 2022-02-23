#include "fileio.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

static inline int is_read(int perm) {
    return (perm & 0x1);
}

static inline int is_write(int perm) {
    return ((perm & 0x2) >> 1);
}

static inline int is_append(int perm) {
    return ((perm & 0x4) >> 2);
}

static inline int is_creat(int perm) {
    return ((perm & 0x8) >> 3);
}

static inline int is_excl(int perm) {
    return ((perm & 0x10) >>4);
}

FileIO::FileIO(){
    m_fileptr = 0;
}

int FileIO::Open(const char *file_name,int perm)
{   
    int permission = 0;
    if(is_read(perm)){
        permission |= O_RDONLY;
    }else if(is_write(perm)){
        permission |= O_WRONLY;
    }else if(is_append(perm)){
        permission |= O_APPEND;
    }else if(is_creat(perm)){
        permission |= O_CREAT; 
    }else if(is_excl(perm)){
        permission |= O_EXCL;
    }
    int res = open(file_name,permission,S_IRWXU);
    if(res == -1){
        return 0;
    } 
    m_fileptr = res;
    return 1;
}

int FileIO::Read(void *buffer,std::size_t bytes_to_read)
{
    int read_res = read(m_fileptr,buffer,bytes_to_read);
    if(read_res == -1){
        return 0;
    }
    return 1;
}

int FileIO::Write(void *buffer,std::size_t bytes_to_write)
{
    int write_res = write(m_fileptr,buffer,bytes_to_write);
    if(write_res == -1){
        return 0;
    }
    return 1;
}

int FileIO::sync()
{
    if(fsync(m_fileptr) == -1){
        return 0;
    }
    return 1;
}

int FileIO::GetFileSize()
{   
    struct stat file_stat;
    int res = fstat(m_fileptr,&file_stat);
    if(res == -1){
        return -1;
    }
    return file_stat.st_size;       
    return 0;
}

long int FileIO::Seek(long int offset,int whence)
{
    int whence_cur = 0;
    if(FILE_SEEK_SET){
        whence_cur = SEEK_SET;
    }else if(FILE_SEEK_END){
        whence_cur = SEEK_END;
    }else if(FILE_SEEK_CUR){
        whence_cur = SEEK_CUR;
    }
    long int offset_t = 0;
    offset_t = lseek(m_fileptr,offset,whence_cur);
    if(offset_t == -1){
        return -1;
    }
    return offset_t;
}

long int FileIO::SeekTell()
{
    long int offset_t = 0;
    offset_t = lseek(m_fileptr,0,SEEK_CUR);
    if(offset_t == -1){
        return -1;
    }
    return offset_t;
}

int FileIO::Close()
{
    if(close(m_fileptr) == -1) {
        return 0;
    }
    return 1;
}