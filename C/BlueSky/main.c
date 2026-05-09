#include <stdio.h>
#include <string.h>

int min_of_three(int one, int two, int three) {
    if ((one - two) < 0) {
        if ((one - three) < 0) {
            return one;
        }
        return two;
    }
    return three;
}

int lev(const char* a, const char* a_end, const char* b, const char* b_end) {
    if ((a_end - a) == 0) {
        return b_end - b;
    }
    if ((b_end - b) == 0) {
        return a_end - a;
    }
    if (a[0] == b[0]) {
        return lev(a + 1, a_end, b + 1, b_end);
    }
    return min_of_three(
        lev(a + 1, a_end, b, b_end),
        lev(a, a_end, b + 1, b_end),
        lev(a + 1, a_end, b + 1, b_end)
    );
}

static int assert_strings_lev(const char *a, const char *b, int expected_lev) {
    int a_len = strlen(a);
    int b_len = strlen(b);

    int lev_value = lev(a, a + a_len - 1, b, b + b_len - 1);
    if (lev_value != expected_lev) {
        printf("Expected %d but lev was %d\n", expected_lev, lev_value);
        // error
        return 1;
    }
    return 0;
}

static int test_case_1(void) {
    const char a[] = "c";
    const char b[] = "c";
    return assert_strings_lev(a, b, 0);
}

static int test_case_2(void) {
    const char a[] = "banana";
    const char b[] = "cabana";
    return assert_strings_lev(a, b, 2);
}

static int test_case_3(void) {
    const char a[] = "print";
    const char b[] = "hello";
    return assert_strings_lev(a, b, 5);
}

#define stringify(a) #a
#define run_test(test_case) {int error = test_case(); if (error) { printf("%s failed\n", stringify(test_case)); errors++; }}

int main() {
    int errors = 0;
    run_test(test_case_1);
    run_test(test_case_2);
    run_test(test_case_3);
    return errors;
}
