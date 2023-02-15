page = [========[

Sometimes, we may need to enclose a piece of code containing something like a = b[c[i]] (notice
the ]] in this code), or we may need to enclose some code that already has some code commented out.
To handle such cases, we can add any number of equals signs between the two opening brackets, as in
[===[. After this change, the literal string ends only at the next closing brackets with the same number
of equals signs in between (]===], in our example). The scanner ignores any pairs of brackets with a
different number of equals signs. By choosing an appropriate number of signs, we can enclose any literal
string without having to modify it in any way.

]========]

io.write(page)