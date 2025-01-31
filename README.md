## bytearray.h
Simple and hackable single header library which makes working with binary data less painful

## Example of reading and writing back a file:
```c
#include "bytearray/bytearray.h"

int main(void){
    ByteArray* filedata = file_to_byte_array("./Pikmin (USA) (v1.01).iso");
    byte_array_to_file(filedata, "./Pikmin (USA) (v1.01).iso");
    cleanup_bytearray(&filedata);
}
```
