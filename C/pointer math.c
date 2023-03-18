// test to see what the difference in addresses is.

#include <stdio.h>
#include <inttypes.h>

int main(void) {
    int32_t array[16];
    int32_t* test1 = &array[0];
    int32_t* test2 = &array[0];
    printf("address of test1 is: %d", test1);
    printf("address of test2 is: %d", test2);
    printf("address difference is: %d", test2 - test1);
    return 0;
}