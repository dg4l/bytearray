#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct{
    uint8_t* buf;
    size_t filesize;
}ByteArray; 

size_t get_file_size(FILE* f){
    struct stat stats;
    int fd = fileno(f); 
    fstat(fd, &stats);
    return stats.st_size;
}

void print_byte_array(ByteArray* ba){
    for (int i = 0; i < ba->filesize; ++i){
        if (!(i % 16)) printf("\n");
        printf("%02X ", ba->buf[i]);
    }
}

void cleanup_bytearray(ByteArray **ba){
    free((*ba)->buf);
    free(*ba);
    *ba = NULL;
}

ByteArray* move_file_into_byte_array(char* filename){
    FILE* f = fopen(filename, "rb");
    if (!f){
        printf("ERROR: FILE NOT FOUND\n");  
        return NULL;
    }
    ByteArray* b = malloc(sizeof(ByteArray));
    b->filesize = get_file_size(f);
    b->buf = malloc(b->filesize * sizeof(uint8_t));
    if (!b->buf){
        printf("ERROR: MEMORY COULD NOT BE ALLOCATED\n");
        fclose(f);
        return NULL;
    }
    fread(b->buf, 1, b->filesize, f);
    fclose(f);
    return b;
}
