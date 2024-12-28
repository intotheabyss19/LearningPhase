local function hello(name)
	print("Hello!", name)
end

local greet = function(name)
	-- .. is a string concatenation
	print("Greetings, " .. name .. "!")
end


-- functions can have multiple return values

local return_four = function()
	return 1, 2, 3, 4
end

first, second, last = return_four()

print("first: ", first)
print("second: ", second)
print("last: ", last) -- the '4' is discarded :(


-- another example
local variable_arguments = function(...)
	local arguments = { ... }
	for i, v in ipairs({...}) do print(i, v) end
	return unpack(arguments)
end

print("-----------------------------")
print("1:", variable_arguments("hello", "world", "!"))
print("-----------------------------")
print("2:", variable_arguments("hello", "not", "world", "?"), "<lost>")

-- 2: will only place the first word hello and discard the rest


-- Function calling
local single_string = function(s)
	return s .. "- WOW!!!"
end

local x = single_string("hi")
local y = single_string "hi" -- can be done for single literal strings and literal tables
print(x , y)


-- emulating default behaviour for functions
local setup = function(opts)
	if opts.default = nil then
		opts.default = 17
	end

	print(opts.default, opts.other)
end

setup { default = 12, other = false }
setup { other = true }


-- Colon functions
local MyTable = {}

function MyTable.something(self, ...) end
function MyTable:something(...) end -- Both are the same things (syntax sugar)
