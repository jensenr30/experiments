-- calculates definite integrals on functions with 1 input
-- calculates area by evaluating f(x) in the middle of the rectangle of width:  
-- x_stepwidth
function integrate_1d(f, x_start, x_stop, x_stepwidth)
  x_stepwidth = math.abs(x_stepwidth)
  if(x_start < x_stop) then
    direction = 1
  elseif(x_start > x_stop) then
    direction = -1
  elseif(x_start == x_stop) then
    return 0
  end
  
  local sum = 0
  x = x_start + x_stepwidth/2.0
  while(x < x_stop) do
    sum = sum + f(x)*x_stepwidth
    x = x + x_stepwidth*direction
  end
  return sum
end