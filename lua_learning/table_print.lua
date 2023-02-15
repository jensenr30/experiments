--[[ 
table_print.lua
Ryan Jensen
2018-12-16
This function will print the structure and contents of a table to the console.
INPUTS:
  - T             REQUIRED   table   the table that will be printed
  - max_level    (optional)  number  max recursive level of tables to print
  - indentation  (optional)  number  number of tabs to print before table info
  - T_original   (optional)  table   this table will be ignored (not printed)
--]]
function table_print(T,max_level,indentation,T_original)
    
    if(type(T) ~= "table") then
    	error("T must be a table. Received type(T) = " .. type(T))
    end
    
    -- assume there is no indentation unless specified by the caller
    if(indentation == nil) then indentation = 0 end
    local tabs = string.rep('\t',indentation)
    -- print "table: #############"
    print(tabs .. tostring(T))
    
    -- avoid printing original table (skip recursive table-printing loops)
    if(T == T_original) then
        return
    end
    if(T_original == nil) then
        T_original = T
    end
    
    -- by default, this function only prints the first level of the table
    if(max_level == nil) then max_level = 1 end
    -- don't print a table where the caller wants to print fewer than 1 levels.
    if(max_level < 1) then return end
    
    for i in pairs(T) do
        local quotes = ''
        if(type(i) == 'string') then quotes = '"' end
        io.write(tabs .. '[' .. quotes .. i .. quotes .. ']' .. '\n')
        if(type(T[i]) == "table") then
            table_print(T[i],max_level-1,indentation+1,T_original)
            io.write('\n')
        elseif(type(T[i]) == "string") then
            print(tabs .. '\t' .. '"' .. T[i] .. '"' .. '\n')
        else
            print(tabs .. '\t' .. tostring(T[i]) .. '\n')
        end
    end
end
