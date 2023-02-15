-- this function creates a vertical plot of random X's
function random_signal_plot(width,height)
    math.randomseed(os.time())
    for r = 1,height do
        x = math.random(0,width-1)
        x = x - x % 1
        for c = 1,x do
            io.write(' ')
        end
        print('X')
    end
end

-- this function creates a vertical plot of random steps
function random_step_plot(width,height)
    x = math.floor(width/2);
    math.randomseed(os.time())
    for r = 1,height do
        -- determine the step direction of x
        if(math.random(0,1) > 0.5) then
            x = x + 1;
        else
            x = x - 1;
        end
        
        x = math.max(1,math.min(width,x))               -- limit the domain of x
       -- advance to the location of x
        for c = 1,x do io.write(' ' ) end print('o')    -- print the location of x
    end
end

function gaussian_plot(width,height,gaussian_number)
    local xlast = math.floor(width/2)
    for r = 1,height do
        local x = 0
        for g = 1,gaussian_number do
            x = x + math.random(-1,1)*width/2
        end
        x = x / math.sqrt(gaussian_number)
        x = math.floor(x/4)
        x = x + math.floor(width/2);
        x = math.max(1,math.min(width,x))           -- limit the domain of x
        for c = 1,math.min(x,xlast)-1 do io.write(' ') end
        for o = 1,math.abs(x-xlast)   do io.write('o') end
        io.write('\n')
        xlast = x
    end
end
