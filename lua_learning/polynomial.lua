--------------------------------------------------------------------------------
-- polynomial.lua
-- Ryan Jensen
-- 2018-12-16
--------------------------------------------------------------------------------
-- this function calculates the numerical value of a polynomial.
-- input (a) is a table containing the coefficients of a polynomial:
--
-- example 1: polynomial  (0.5 x^3) + (2.1 x^2) + x  is represented by:
-- a[1] = 1    a[2] = 2.1    a[3] = 0.5
--
-- example 2: polynomial x^2 + 5x + 13 - 5/x + 25/x^2 is represented by:
-- a[-2] = 25    a[-1] = -5    a[0] = 13    a[1] = 5    a[2] = 1
--
-- non-integer polynomials can be evaluated in exactly the same way:
-- example 3: polynomial x^2.4 + 0.5x^2.3 + 0.1x^0.5 is represented by:
-- a[0.5] = 0.1    a[2.3] = 0.5    a[2.4] = 1
--
-- nil entries are treated as zeros (ignored)
-- if the table contains string keys (i.e. a.color) they are ignored
-- --------------------------------------------------------------------------------
function poly_evaluate(a,x)

	if(type(x) ~= "number") then
		error("x is not a number! x must be a number.")
	end

	local sum = 0

	for e in pairs(a) do
		if(type(e) == "number") then
			sum = sum + (a[e] * x^e)
		end
	end
	return sum
end
