-- this program will tell the user what the resolution of Lua's numbers is.

require("round")

function lua_number_resolution()
    local minuend = 1
    local subtrahend = minuend
    local division_factor = 0.99
    local found_resolution = false

    repeat
        subtrahend = subtrahend * division_factor
        
        if(minuend - subtrahend == minuend) then
            found_resolution = true;
        end
    until (found_resolution == true)
    return subtrahend,minuend
end


function lua_number_resolution_print()
    local subtrahend
    local minuend
    
    subtrahend,minuend = lua_number_resolution()

    print("");
    print("The maximum value that can be added to the value of "..minuend.." without changing its value is "..subtrahend..".")
    print("This implies that the resolution is ".. (subtrahend/minuend)*100 .." %.")
    print("This is the same as ".. (subtrahend/minuend)*1e6 .." ppm.")
    print("This is the same as ".. (subtrahend/minuend)*1e9 .." ppb.")
    print("This is the same as ".. (subtrahend/minuend)*1e12 .." ppt.")

    print("This implies ".. lua_number_bits() .." bits of precision.")
    
    print("An error of half a bit is equal to roughly")
end

function lua_number_bits()
    local subtrahend
    local minuend
    subtrahend,minuend = lua_number_resolution()
    return math.tointeger(round(-math.log(subtrahend,2)))
end

function lua_integer_bits()
    return round( math.log(math.maxinteger,2)+1 )
end