-- this function MAXES OUT your CPU's clock cycles.
-- the purpose of this function is to heat up your computer.
function sleep(milliseconds)
    time_at_start = os.clock()
    -- wait until it is at least [milliseconds] past when this function started
    while ( os.clock()-time_at_start < milliseconds/1000.0 ) do
        -- do nothing while you wait
    end
end