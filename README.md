## bytearray.h
Simple and hackable single header library for working with binaries.

## Definition of a ByteArray:
```c
typedef struct{
    uint8_t* buf;
    size_t size;
}ByteArray; 
```

## Example of file I/O and error handling:
```c
#include "bytearray/bytearray.h"

int main(void){
    char* filename = "example_file.bin";
    ByteArray* filedata = file_to_byte_array(filename);
    if (!filedata){
        printf("Read Error!\n");
        return -1;
    }
    if (!byte_array_to_file(filedata, filename)){
        printf("Write Error!\n");
        return -1;
    }
    cleanup_bytearray(&filedata);
}
```
