#include <stdio.h>

int main(void) {
    for (int semitones = -12; semitones <= 12; semitones++) {
        float octaves = semitones / 12.0f;
        printf("semitones %2d  octaves %10.4f\n", semitones, octaves);
    }
}
