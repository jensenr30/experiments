#include <stdio.h>
#include <stdint.h>

uint32_t overflow_by(int32_t over) {
     
    return UINT32_MAX + 1 + over;
}

int main(void) {
    for (int32_t i = 0; i < 5000; i+=1000) {
        uint64_t value = 
        printf("overflow by %u: %u\n", i, overflow_by(i));
    }
}
