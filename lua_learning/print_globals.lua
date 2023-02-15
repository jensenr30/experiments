-- this script will print all of the global variables
function print_globals()
    local number_of_globals = 0
    for n in pairs(_G) do
        print(n)
        number_of_globals = number_of_globals + 1
    end
    return number_of_globals
end
