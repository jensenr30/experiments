function isbool(input)
    
    if(input == false) then
        return true
    end
    
    if(input == true) then
        return true
    end
    
    return false
    
end

print("isbool(true) = "..tostring(isbool(true)))
print("isbool(false) = "..tostring(isbool(false)))
print("isbool(nil) = "..tostring(isbool(nil)))
print("isbool(5) = "..tostring(isbool(5)))
print("isbool('hello') = "..tostring(isbool('hello')))
print("isbool(isbool) = "..tostring(isbool(isbool)))