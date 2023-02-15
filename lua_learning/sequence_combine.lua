-- sequence_combine.lua
-- Ryan Jensen
-- 2018-12-23
-- this file contains a function to combine two sequences.

--------------------------------------------------------------------------------
-- this function will combine two sequences.  The second sequence (b) will be
-- inserted into the first sequence (a) at the index [pos].
-- If pos is 1,   the resulting sequence will be {b,a}.
-- If pos is nil, the resulting sequence will be {a,b}.
-- if pos is n,   the resulting sequence will be {a[1:n-1],b,
-- notice that sequence b never gets split up.  Sequence a gets split up in
-- order to accommodate sequence b.
--------------------------------------------------------------------------------
function sequence_combine(a,b,pos)
	if(type(a) ~= "table") then
		error("a must be a table")
	end
	if(type(b) ~= "table") then
		error("b must be a table")
	end
	if(type(pos) ~= "number") then
		error("pos must be a number")
	end
	if(pos < 1) then
		error("pos cannot be less than 1")
	end
	if(pos > #a+1) then
		error("pos cannot be greater than 1 + the length of a.    1 + #a = " .. 1 + #a)
	end
	
	N = #a + #b
	combined ={}
	i = 1
	-- put the first bit of a[] into the c[] table
	while(i < pos) do
		table.insert(combined,a[i])
		i = i + 1
	end
	-- put the entire b[] into the c[] table 
	while(i-pos+1 <= #b) do
		table.insert(combined,b[i-pos+1])
		i = i + 1
	end
	-- put the rest of the a[] table into the c[] table
	while(i-#b <= #a) do
		table.insert(combined,a[i-#b])
		i = i + 1
	end
	return combined
end
