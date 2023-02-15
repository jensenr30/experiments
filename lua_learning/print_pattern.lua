-- this function will print a pattern of X's on the screen based on the input parameters:
-- width = the width of the canvas  drawing area.
-- height = the height of the canvas / drawing area.
-- mod    = how frequently an X is printed
function print_pattern(width, height, mod)
    for r = 1,height do
        for c = 1,width do
            if( (c + r*width) % mod == 0) then
                io.write("X")
            else
                io.write(" ")
            end
        end
        io.write("\n")
    end
end
