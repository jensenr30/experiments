
printResult = ""

-- this function will print all the arguments you give it.  it just works perfectly.  cool.
function print_shaft (...)
    for i,v in ipairs(arg) do
        printResult = printResult .. tostring(v) .. "\t"
    end
    print("print_shaft received "..arg.n.." arguments.")
    
    if(0) then
        print("0 is true!");
    else
        print("0 is false!");
    end
end

print_shaft("hello",5,'world', 'So far, I am enjoying how the Lua language is set up.',23.4569219482)

print(printResult)