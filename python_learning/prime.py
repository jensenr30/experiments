# prime.py
# Ryan Jensen
# 2019-01-19
"""Provide functions to satisfy some curiosity around prime numbers!"""

#===============================================================================
# module importation
import math
import time

#===============================================================================
def gen(n,report_gen_time=0):
    """Generate the first [n] prime numbers starting at 2.
    
    The second argument [report_gen_time] is optional.  If you choose to send a
    value for [report_gen_time], this function will print the amount of time
    (seconds) it takes to generate [report_gen_time] prime numbers.
    
    Returns a tuple:
    ([list_of_prime_numbers],[list_of_generation_times])"""
    
    i = 2
    primes = []
    primes_found = 0
    time_start = time.time()
    time_last = time_start
    time_per_batch = []
    
    while primes_found < n:
        # assume i is a prime; then try to prove this assumption is wrong.
        i_is_prime = 1
        i_sqrt_floor = math.floor(math.sqrt(i))
        for p in primes:
            if p > i_sqrt_floor:
                i_is_prime = 1
                break
            quotient = i/p
            if int(quotient) == quotient:
                i_is_prime = 0
                break
            
        if i_is_prime:
            primes.append(i)
            primes_found += 1
            if primes_found and primes_found % report_gen_time == 0:
                time_now = time.time()
                time_elapsed = time_now - time_last
                time_per_batch.append(time_elapsed)
                print(
                    "primes_found=" + str(primes_found)
                    + "\ttime since last report=" + str(time_now-time_last))
                time_last = time_now
                
        i += 1
    return (primes,time_per_batch)
#

    
#===============================================================================
def test():
    """Run some arbitrary test involving prime numbers."""
    # generate some prime numbers
    n = 1e6
    report_gen_time = 1e3
    my_primes = gen(n,report_gen_time)
    # write the prime numbers to a file
    output_file = open('primes.csv','w')
    output_file.write("prime\n")
    i = 1;
    for p in my_primes:
        output_file.write(str(p) + "\n")
        #print(str(i) + ":  \t" + str(p))
        i += 1
    output_file.close()
#
test();
