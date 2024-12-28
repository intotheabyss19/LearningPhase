-- List
local list = {"first", 2, false, function() print("Fourth!") end } -- heterogeneous list
print("Yup, 1-indexed:", list[1])
print("Fourth is 4 ... :", list[4]())

-- Maps
local t = {
	literal_key = "a string", -- this is a key
	["an expression"] = "also works", -- this is also a key
	[function() end] = true -- functions also work
}

print("literal_key : ", t.literal_key)
print("an expression" : ", t["an expression"])
print("function() end: ", t[function() end])
