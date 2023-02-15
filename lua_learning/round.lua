-- this function will return a rounded version of the input number.
-- examples:
    -- round(5.123)      --> 5.0
    -- round(0.123456,3) --> 0.123
    -- round(123456,-3)  --> 123000.0  this works in reverse. so cool! 
function round(x,decimal_places)
    local mult = math.pow(10,decimal_places or 0)
    x = x * mult
    if(x%1 >= 0.5) then
        x = math.ceil(x)
    else
        x = math.floor(x)
    end
    return x/mult
end
