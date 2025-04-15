#pragma once
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>

typedef struct{
    uint8_t* buf;
    size_t bufsize;
}ByteArray; 

/*                          API                                 */
/* ------------------------------------------------------------ */

size_t get_file_size(FILE* f);

void print_byte_array(ByteArray* ba);

void cleanup_bytearray(ByteArray **ba);

ByteArray* create_empty_byte_array(size_t size);

bool byte_array_to_file(ByteArray* ba, char* filename);

ByteArray* file_to_byte_array(char* filename);

void insert_zeroes(size_t pos, size_t amt, ByteArray** ba);

/* -------------------------------------------------------------- */

