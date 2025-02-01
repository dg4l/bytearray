#pragma once
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>

typedef struct{
    uint8_t* buf;
    size_t bufsize;
}ByteArray; 

size_t get_file_size(FILE* f){
    struct stat stats;
    int fd = fileno(f); 
    fstat(fd, &stats);
    return stats.st_size;
}

void print_byte_array(ByteArray* ba){
    for (int i = 0; i < ba->bufsize; ++i){
        if (!(i % 16)) printf("\n");
        printf("%02X ", ba->buf[i]);
    }
}

void cleanup_bytearray(ByteArray **ba){
    free((*ba)->buf);
    free(*ba);
    *ba = NULL;
}

ByteArray* create_empty_byte_array(size_t size){
    ByteArray* b = malloc(sizeof(ByteArray));
    if (!b){
        return NULL;
    }
    b->bufsize = size;
    b->buf = calloc(b->bufsize, 1);
    if (!b->buf){
        return NULL;
    }
    return b;
}

bool byte_array_to_file(ByteArray* ba, char* filename){
    FILE* fp = fopen(filename, "wb");
    if (!fp) return 0;
    fwrite(ba->buf, 1, ba->bufsize, fp);
    fclose(fp);
    return 1;
}

ByteArray* file_to_byte_array(char* filename){
    FILE* f = fopen(filename, "rb");
    if (!f){
        return NULL;
    }
    ByteArray* b = create_empty_byte_array(get_file_size(f));
    fread(b->buf, 1, b->bufsize, f);
    fclose(f);
    return b;
}
