-- clears the screen by printing a n newlines
function clear(n)
    if(n == nil) then n = 100 end
    io.write(string.rep('\n',n))
end