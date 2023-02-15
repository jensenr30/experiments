require("si_prefix")
require("number_resolution")

-- roughly 
function number_to_text(x)
    local exponent = math.log(x,10)
    local exponent_int = math.floor(exponent)
    local si_number = math.floor(exponent/3)*3
    local coefficient = x / math.pow(10,exponent_int)
    
    local pre = si_prefix[si_number]
    
    x = x / math.pow(10,si_number)
    
    local prepre
    
    if(x >= 100) then
        prepre = "hundred"
    elseif(x >= 10) then
        prepre = "ten"
    else
        prepre = ""
    end
    
    return "" .. math.tointeger(round(coefficient)) .. " " .. prepre .. " " .. pre
    
end
