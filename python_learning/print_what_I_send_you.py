# print_what_I_send_you.py
# Ryan Jensen
# 2018-12-31
# This function will print the arguments it receives.

def print_what_I_send_you(*args, **keywords):
    for i in range(len(args)):
        print("[" + str(i) + "] = " + str(args[i]))
    
    for key in keywords:
        print(str(key) + "\t" + str(keywords[key]))
        
print_what_I_send_you(1,2,3,vector="victor",ECHO="echo",roger="Roger")