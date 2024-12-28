local fruits = { "apple", "mango", "orange" }
for index = 1, #fruits do
	print(index, fruits[index])
end
-- above iteration only works for arrays, for maps it won't do anything
-- we can thus use pairs() function to run the same thing over maps

local scores = { team1 = 5, team2 = 6.7, team3 = -2, team4 = "N/A" }
for index, value in ipairs(fruits) do -- ipairs === integer pairs
	print(index, value)
end

-- using pairs over map
local scores = { team1 = 5, team2 = 6.7, team3 = -2, team4 = "N/A" }
for key, value in pairs(scores) do
	print(key, value)
end
