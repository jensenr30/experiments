--
local function main()
	print("main() start.")
	io.stdout:setvbuf('no')
	
	require "table_print"
	require "sequence_combine"
	a = {10,20,30,1000,2000,3000}
	b = {-100,-200,-300}
	pos = 7
	comb = sequence_combine(a,b,pos)
	table_print(comb)
	
	table.sort(comb)
	table_print(comb)
	
	d= table.concat({"hello", " mother", " earth"})
	
	print(d)
	table_print(d)
	
	
--	require "polynomial"
--	require "integrate"
--	local a = {[0]=1, [1]=1, [2]=1, [3]=1, [4]=1, [5]=1}
--	local start = 0
--	local step  = 0.0001
--	local stop  = 1
--	local x = start
--	local function f(x) return poly_evaluate(a,x) end
--	local sum = integrate_1d(f, start, stop, step)
--	print(sum)
end
main()
