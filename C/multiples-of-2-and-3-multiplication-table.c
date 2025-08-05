#include <stdio.h>
#include <math.h>

float eq_x = 0.5;
float eq_y = 0.8660254037844386467637231707529361834714026269051903140279034897;

static const int marg_width = 3;
static const int marg_height = 2;

void print_header() {
    printf("h  / w ");
    for (int w = 2 * marg_width; w <= 2 * marg_width * 6; w += 2 * marg_width) {
        printf("  %2d      ", w);
    }
    printf("\n");
}

void print_aspect_ratios_error_to_1() {
    for (int h = marg_height; h <= 32; h += marg_height) {
        printf("%2d    ", h);
        for (int w = 2 * marg_width; w <= 2 * marg_width * 6; w += 2 * marg_width) {
            float visual_aspect_ratio = w * eq_x / (h * eq_y);
            printf("%8.4f  ", fabs(1 - visual_aspect_ratio));
        }
        printf("\n");
    }
}

void print_aspect_ratios() {
    for (int h = marg_height; h <= 32; h += marg_height) {
        printf("%2d    ", h);
        for (int w = 2 * marg_width; w <= 2 * marg_width * 6; w += 2 * marg_width) {
            float visual_aspect_ratio = w * eq_x / (h * eq_y);
            printf("%8.4f  ", visual_aspect_ratio);
        }
        printf("\n");
    }
}

void print_tiles_per_chunk() {
    for (int h = marg_height; h <= 32; h += marg_height) {
        printf("%2d    ", h);
        for (int w = 2 * marg_width; w <= 2 * marg_width * 6; w += 2 * marg_width) {
            printf("%8d  ", h * w);
        }
        printf("\n");
    }
}

int main(void) {
    print_header();
    print_aspect_ratios();
    printf("\n\n");
    print_header();
    print_aspect_ratios_error_to_1();
    printf("\n\n");
    print_header();
    print_tiles_per_chunk();
    return 0;
}
