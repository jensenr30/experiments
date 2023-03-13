# sums all digits of a signed integer.
# supports the use of non-integer bases; your mileage may vary.
def sum_digits(x: int, base=10):
    sum = 0
    if x < 0:
        x *= -1
    x = int(x)
    while x >= 1:
        sum += x % base
        x = x // base
    return sum