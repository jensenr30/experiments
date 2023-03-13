from sum_digits import sum_digits as sd

def clock_digits_sum(hours: int, minutes: int, seconds: int = 0):
    return sd(hours) + sd(minutes) + sd(0)