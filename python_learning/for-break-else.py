# for_break_else.py
# Ryan Jensen
# 2018-12-31
# this script demonstrates the for-break-else structure of python.

breaker_tripper = int(input("Please enter a number for the breaker tripper: "))
n = 20
print("now counting from 0 to " + str(n-1))
for i in range(0,n):
    print(i)
    if(i == breaker_tripper):
        print("tripped the breaker!")
        break
else:
    print("did not trip the breaker.")
