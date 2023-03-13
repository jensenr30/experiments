# print all occurrences in 12 hours where the digits of a digital clock (HH:MM) add up to a certain value.

from clock_digits_sum import clock_digits_sum
from sum_digits import sum_digits


# test clock_digits_sum
h = 1
m = 0
target_val = 13
occurrences = 0
while h <= 12:
    sum = clock_digits_sum(h, m)
    if sum == target_val:
        print('{:02}:{:02}'.format(h, m))
        occurrences += 1
    m = (m + 1)
    if m >= 60:
        m -= 60
        h += 1
print(f"On a digital clock, in 12 hours from 1 pm to 12:59, the number of times the digits add up to {target_val} is {occurrences}.")

# test sum_digits()
# a list of tuples with format (sum_of_digits, test_value, base=10)
test_vectors = [
    (21,    123456.89       ),
    (6,     42              ),
    (9,     111111111       ),
    (1,     16,         16  ),
    (16,    31,         16  ),
    (35,    98765           ),
]
for v in test_vectors:
    expected_sum_val = v[0]
    test_val = v[1]
    base = 10
    if len(v) == 2:
        sum = sum_digits(test_val)
    elif len(v) == 3:
        base = v[2]
        sum = sum_digits(test_val, base)
    if sum == expected_sum_val:
        print(f"PASS. The sum of the digits in the base-{base}-number {test_val} is: {sum} ")
    else:
        raise Exception(f"test_sum_digits failed with test vector: {v}")
