# for.py
# Ryan Jensen
# 2018-12-31
# this script is to play around with for loops

words = ["These", "Are", "Some", "Of", "My", "Favorite", "Words"]

for w in words:
    print(len(w),w)

for i in range(len(words)):
    print("\"" + words[i] + "\" is the [" + str(i) + "] element")
