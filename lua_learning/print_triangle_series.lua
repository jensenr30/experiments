

T = tonumber(arg[1])
print(T)
print(type(T))

for t=1,T do
    arg = {t};
    dofile("print_triangle.lua")
end
