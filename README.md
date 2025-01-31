## bytearray.h
Simple and hackable single header library for working with binaries.

## Example of reading and writing back a file:
```c
#include "bytearray/bytearray.h"

int main(void){
    char* filename = "example_file.bin";
    ByteArray* filedata = file_to_byte_array(filename);
    byte_array_to_file(filedata, filename);
    cleanup_bytearray(&filedata);
}
```
