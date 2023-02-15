require("round")
function sigfig(x,sigfigs)
    local sigfigs = round(sigfigs)
    
    local exponent = math.log(x,10)
    local exponent_int = math.floor(exponent)
    local power_of_ten = math.pow(10,exponent_int)
    local coefficient = x/power_of_ten
    
    local mult = math.pow(10,sigfigs-1)
    local coefficient_rounded = round(coefficient*mult)/mult
    
    return coefficient_rounded*power_of_ten
end