#include "bytearray.h"

void insert_zeroes(size_t pos, size_t amt, ByteArray** ba){
    ByteArray* tmp = create_empty_byte_array((*ba)->size + amt);
    memcpy(tmp->buf, (*ba)->buf, pos);
    memset(&tmp->buf[pos], 0, amt);
    memcpy(&tmp->buf[pos + amt], &(*ba)->buf[pos], (*ba)->size - pos);
    cleanup_bytearray(ba);
    *ba = tmp;
}

size_t get_file_size(FILE* f){
    struct stat stats;
    int fd = fileno(f); 
    fstat(fd, &stats);
    return stats.st_size;
}

void print_byte_array(ByteArray* ba){
    for (size_t i = 0; i < ba->size; ++i){
        if (!(i % 16)) printf("\n");
        printf("%02X ", ba->buf[i]);
    }
    printf("\n");
}

void cleanup_bytearray(ByteArray** ba){
    free((*ba)->buf);
    free(*ba);
    *ba = NULL;
}

ByteArray* clone_byte_array(ByteArray* ba){
    ByteArray* ret = create_empty_byte_array(ba->size);
    if (!ret){
        return NULL;
    }
    memcpy(ret->buf, ba->buf, ba->size);
    return ret;
}

ByteArray* create_empty_byte_array(size_t size){
    ByteArray* b = malloc(sizeof(ByteArray));
    if (!b){
        return NULL;
    }
    b->size = size;
    b->buf = calloc(b->size, 1);
    if (!b->buf){
        free(b);
        return NULL;
    }
    return b;
}

bool byte_array_to_file(ByteArray* ba, char* filename){
    FILE* fp = fopen(filename, "wb");
    if (!fp) return 0;
    fwrite(ba->buf, 1, ba->size, fp);
    fclose(fp);
    return 1;
}

ByteArray* file_to_byte_array(char* filename){
    FILE* f = fopen(filename, "rb");
    if (!f){
        return NULL;
    }
    ByteArray* b = create_empty_byte_array(get_file_size(f));
    fread(b->buf, 1, b->size, f);
    fclose(f);
    return b;
}
