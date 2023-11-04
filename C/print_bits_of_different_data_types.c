#include <stdbool.h>
#include <stdio.h>

static void print_bits_int(int number) {
    for (int i = sizeof(int)*8 - 1; i >= 0; i--) {
        bool bit = (number & (1 << i)) >> i;
        printf("%d", bit);
    }
}

static void print_bits_int_extra(int number) {
    printf("int: %9d    bits: ", number);
    print_bits_int(number);
    printf("\n");
}

int main(void) {
    int int_bits = sizeof(int) * 8;
    printf("sizeof(int): %ld bytes (%d bits)\n", sizeof(int), int_bits);
    for (int i = 4; i >= -4; i--)
        print_bits_int_extra(i);
}